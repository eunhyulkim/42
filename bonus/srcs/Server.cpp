#include "Server.hpp"
#include "ServerManager.hpp"

extern int g_server_live;

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::Server() {}

Server::Server(ServerManager* server_manager, const std::string& server_block, std::vector<std::string>& location_blocks, Config* config)
{
	std::map<std::string, std::string> server_map = ft::stringVectorToMap(ft::split(server_block, '\n'), ' ');
	struct sockaddr_in server_addr;
	std::string uri;
	std::string block;
	std::string error_page;
	std::string line;

	m_manager = server_manager;
	m_config = config;
	if (ft::hasKey(server_map, "server_name"))
		m_server_name = server_map["server_name"];
	else
		m_server_name = "noname";
	m_host = server_map["host"];
	m_port = ft::stoi(server_map["port"]);
	m_request_uri_limit_size = ft::stoi(server_map["REQUEST_URI_LIMIT_SIZE"]);
	m_request_header_limit_size = ft::stoi(server_map["REQUEST_HEADER_LIMIT_SIZE"]);
	m_limit_client_body_size = ft::stoi(server_map["LIMIT_CLIENT_BODY_SIZE"]);
	m_default_error_page = ft::getStringFromFile(server_map["DEFAULT_ERROR_PAGE"]);
	m_worker_count = ft::stoi(server_map["WORKER"]);
	m_health_check_interval = -1;
	if (ft::hasKey(server_map, "HEALTH_CHECK_INTERVAL"))
		m_health_check_interval = ft::stoi(server_map["HEALTH_CHECK_INTERVAL"]);
	if (m_health_check_interval < 1)
		m_health_check_interval = 5;
	if((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("SOCKET ERROR");
	int value = true;
	if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
	server_addr.sin_port = ft::ws_htons(m_port);
	if(bind(m_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(struct sockaddr)) == -1)
		throw std::runtime_error("BIND ERROR");
	if(listen(m_fd, 256) == -1)
		throw std::runtime_error("LISTEN ERROR");
	if (fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("FCNTL ERROR");
	m_manager->fdSet(m_fd, ServerManager::READ_SET);
	if (m_manager->get_m_max_fd() < m_fd)
		m_manager->set_m_max_fd(m_fd);
	for (std::vector<std::string>::iterator it = location_blocks.begin(); it != location_blocks.end(); ++it)
	{
		uri = ft::split(ft::split(*it).front(), ' ')[1];
		block = *it;
		block = block.substr(block.find('\n') + 1);
		m_locations.push_back(Location(uri, block, m_limit_client_body_size));
	}
	m_server_live = new bool(true);
	m_job_queue = new std::queue<Job>;
	pthread_mutex_init(&m_job_mutex, NULL);
	pthread_mutex_init(&m_live_mutex, NULL);
	writeCreateServerLog(m_host, m_port);
}

Server::Server(const Server& copy)
{
	m_manager = copy.m_manager;
	m_server_name = copy.m_server_name;
	m_host = copy.m_host;
	m_port = copy.m_port;
	m_fd = copy.m_fd;
	m_request_uri_limit_size = copy.m_request_uri_limit_size;
	m_request_header_limit_size = copy.m_request_header_limit_size;
	m_limit_client_body_size = copy.m_limit_client_body_size;
	m_default_error_page = copy.m_default_error_page;
	m_config = copy.m_config;
	m_locations = copy.m_locations;
	m_connections = copy.m_connections;
	m_responses = copy.m_responses;
	m_server_live = copy.m_server_live;
	m_job_queue = copy.m_job_queue;
	m_job_mutex = copy.m_job_mutex;
	m_live_mutex = copy.m_live_mutex;
	m_uri_mutex = copy.m_uri_mutex;
	m_workers = copy.m_workers;
	m_worker_count = copy.m_worker_count;
	m_health_check_interval = copy.m_health_check_interval;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::~Server(){}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Server& Server::operator=(const Server& obj)
{
	if (this == &obj)
		return (*this);
	m_manager = obj.m_manager;
	m_server_name = obj.m_server_name;
	m_host = obj.m_host;
	m_port = obj.m_port;
	m_fd = obj.m_fd;
	m_request_uri_limit_size = obj.m_request_uri_limit_size;
	m_request_header_limit_size = obj.m_request_header_limit_size;
	m_limit_client_body_size = obj.m_limit_client_body_size;
	m_default_error_page = obj.m_default_error_page;
	m_config = obj.m_config;
	m_locations = obj.m_locations;
	m_connections = obj.m_connections;
	m_responses = obj.m_responses;
	m_server_live = obj.m_server_live;
	m_job_queue = obj.m_job_queue;
	m_job_mutex = obj.m_job_mutex;
	m_live_mutex = obj.m_live_mutex;
	m_uri_mutex = obj.m_uri_mutex;
	m_workers = obj.m_workers;
	m_worker_count = obj.m_worker_count;
	m_health_check_interval = obj.m_health_check_interval;

	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Server& server)
{

	out << "server_name: " << server.get_m_server_name() << std::endl;
	out << "host: " << server.get_m_host() << std::endl;
	out << "port: " << server.get_m_port() << std::endl;
	out << "server_fd: " << server.get_m_fd() << std::endl;
	out << "request_uri_limit_size: " << server.get_m_request_uri_limit_size() << std::endl;
	out << "request_header_limit_size: " << server.get_m_request_header_limit_size() << std::endl;
	out << "limit_client_body_size: " << server.get_m_limit_client_body_size() << std::endl;
	out << "default_error_page: " << server.get_m_default_error_page() << std::endl;
	out << "--------CONFIG----------" << std::endl;
	out << *(server.get_m_config()) << std::endl;
	out << "--------LOCATIONS----------" << std::endl;
	for (std::vector<Location>::const_iterator it = server.get_m_locations().begin(); it != server.get_m_locations().end(); ++it) {
		out << *it << std::endl;
	}
	std::cout << "--------CONNECTIONS----------" << std::endl;
	for (std::map<int, Connection>::const_iterator it = server.get_m_connections().begin(); it != server.get_m_connections().end(); ++it) {
		out << it->second << std::endl;
	}
	std::cout << "--------NEXT RESPONSE----------" << std::endl;
	if (server.get_m_responses().size() > 0)
		out << server.get_m_responses().front() << std::endl;
	else
		out << "Response is not exist." << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const std::string& Server::get_m_server_name() const { return (this->m_server_name); }
const std::string& Server::get_m_host() const { return (this->m_host); }
int Server::get_m_port() const { return (this->m_port); }
int Server::get_m_fd() const { return (this->m_fd); }
size_t Server::get_m_request_uri_limit_size() const { return (this->m_request_uri_limit_size); }
size_t Server::get_m_request_header_limit_size() const { return (this->m_request_header_limit_size); }
size_t Server::get_m_limit_client_body_size() const { return (this->m_limit_client_body_size); }
const std::string& Server::get_m_default_error_page() const { return (this->m_default_error_page); }
Config* Server::get_m_config() const { return (this->m_config); }
const std::vector<Location>& Server::get_m_locations() const { return (this->m_locations); }
const std::map<int, Connection>& Server::get_m_connections() const { return (this->m_connections); }
const std::queue<Response>& Server::get_m_responses() const { return (this->m_responses); }
bool Server::get_m_server_live() const { return (*(this->m_server_live)); }
std::queue<Job>* Server::get_m_job_queue() const { return (this->m_job_queue); }
int Server::get_m_worker_count() const { return (this->m_worker_count); }
int Server::get_m_health_check_interval() const { return (this->m_health_check_interval); }

namespace {
	bool isWorkerFree(Worker* worker)
	{
		return (worker->isFree());
	}
}
int Server::getFreeWorkerCount() const { return std::count_if(m_workers.begin(), m_workers.end(), isWorkerFree); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* -------------------------- CONNECTION MANAGEMENT ------------------------- */
/* ************************************************************************** */

bool
Server::hasNewConnection()
{
	return (m_manager->fdIsset(m_fd, ServerManager::READ_COPY_SET));
}

Job
Server::acceptNewConnection()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size = sizeof(struct sockaddr);
	int 				client_fd;
	std::string			client_ip;
	Job 				ret;

	ret.client_fd = -1;
	ft::bzero(&client_addr, client_addr_size);

	if ((client_fd = accept(m_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1) {
		ft::log(ServerManager::log_fd, ft::getTimestamp() + "[Failed][Function]failed to cerate client_fd by accept function");
		return (ret);
	}
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (ret);
	ret.client_fd = client_fd;
	ret.ip = ft::inet_ntoa(client_addr.sin_addr.s_addr);
	ret.port = static_cast<int>(client_addr.sin_port);
	return (ret);
}

Server* Server::clone() { return (new Server(*this)); }

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Server::createWorkers()
{
	for (int i = 0; i < m_worker_count; ++i)
		m_workers.push_back(new Worker(m_manager, this, &m_job_mutex, &m_live_mutex, &m_uri_mutex, i + 1));
}

void
Server::runWorkers()
{
	std::vector<Worker *>::iterator it = m_workers.begin();
	for (; it != m_workers.end(); ++it)
		(*it)->run();
}

bool
Server::isExistFreeWorker()
{
	std::vector<Worker *>::iterator it = m_workers.begin();
	for (; it != m_workers.end(); ++it)
	{
		if ((*it)->isFree())
			return (true);
	}
	return (false);
}

void
Server::run()
{
	Job new_job;

	if (hasNewConnection())
	{
		writeDetectNewConnectionLog();
		while (!isExistFreeWorker())
		{
			usleep(100); // change to macro EVERAGE_WORK_USECOND
			if (!g_server_live)
				return ;
		}
		if ((new_job = acceptNewConnection()).client_fd == -1)
		{
			perror("accept connection fail:");
			reportCreateNewConnectionLog();
		}
		else {
			m_job_queue->push(new_job);
			writeCreateNewConnectionLog(new_job.client_fd, new_job.ip, new_job.port);
		}
	}
}

void
Server::exit() {
	*m_server_live = false;
	int worker_count = m_workers.size();
	for (int i = worker_count - 1; i >= 0; --i)
	{
		m_workers[i]->exit();
		delete m_workers[i];
	}
	close(m_fd);
	pthread_mutex_destroy(&m_job_mutex);
	pthread_mutex_destroy(&m_live_mutex);
	std::map<std::string, pthread_mutex_t>::iterator uri_it = m_uri_mutex.begin();
	for (; uri_it != m_uri_mutex.end(); ++uri_it)
		pthread_mutex_destroy(&uri_it->second);
	delete m_server_live;
	delete m_job_queue;
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Server::writeCreateServerLog(std::string host, int port)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Server][" + host + ":" + ft::to_string(port) + "]";
	text += " server created successfully.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Server::writeDetectNewConnectionLog()
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Detected][Connection][Server:" + m_server_name + "][" + m_host + ":" + ft::to_string(m_port) + "] ";
	text += "new connection detected.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Server::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Connection][Server:" + m_server_name + "][" + m_host + ":" + ft::to_string(m_port) + "]";
	text += "[Client:" + client_ip + ":" + ft::to_string(client_port) + "] new connection(client fd:" + ft::to_string(client_fd);
	text += ") created and added to job queue.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Server::reportCreateNewConnectionLog()
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Detected][Connection][Server:" + m_server_name + "][" + m_host + ":" + ft::to_string(m_port) + "] ";
	text += "new connection failed.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}
