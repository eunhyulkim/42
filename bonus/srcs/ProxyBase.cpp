#include "ProxyBase.hpp"
#include "ServerManager.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ProxyBase::ProxyBase() {}

ProxyBase::ProxyBase(ServerManager* server_manager, const std::string& proxy_block)
{
	std::map<std::string, std::string> proxy_map = ft::stringVectorToMap(ft::split(proxy_block, '\n'), ' ');
	struct sockaddr_in server_addr;

    m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);

	m_manager = server_manager;
	m_host = proxy_map["host"];
	m_port = ft::stoi(proxy_map["port"]);
	std::string type = proxy_map["type"];
	if (type == "cache" || type == "Cache")
		m_type = CACHE_PROXY;
	else if (type == "LoadBalance" || type == "loadBalance")
		m_type == LOADBALANCE_PROXY;
	else if (type == "filter" || type == "Filter")
		m_type == FILTER_PROXY;
	else
		throw (std::invalid_argument("filter type invalid."));
	
	std::vector<std::string> servers = ft::split(ft::trim(proxy_map["server"], "[]"), ',');
	std::vector<std::string>::iterator it = servers.begin();
	for (; it != servers.end()!; ++it)
	{
		std::vector<std::string> server_url = ft::split(*it, ':');
		m_servers.insert(std::pair<std::string, int>(ft::trim(server_url[0], " "), ft::stoi(ft::trim(server_url[1], " "))));
	}

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
}

ProxyBase::ProxyBase(const ProxyBase& copy)
{
	m_manager = copy.m_manager;
	m_type = copy.m_type;
	m_host = copy.m_host;
	m_port = copy.m_port;
	m_fd = copy.m_fd;
	m_max_fd = copy.m_max_fd;
	m_read_set = copy.m_read_set;
	m_read_copy_set = copy.m_read_copy_set;
	m_write_set = copy.m_write_set;
	m_write_copy_set = copy.m_write_copy_set;
	m_servers = copy.m_servers;
	m_connections = copy.m_connections;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ProxyBase::~ProxyBase()
{
	m_manager = NULL;
	m_type = UNDEFINED_PROXY;
	m_host.clear();
	m_port = 0;
	m_fd = -1;
	m_max_fd = 0;
	ft::fdZero(&m_read_set);
	ft::fdZero(&m_read_copy_set);
	ft::fdZero(&m_write_set);
	ft::fdZero(&m_write_copy_set);
	m_servers.clear();
	m_connections.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ProxyBase& ProxyBase::operator=(const ProxyBase& obj)
{
	if (this == &obj)
		return (*this);
	m_manager = obj.get_m_manager();
	m_type = obj.get_m_type();
	m_host = obj.get_m_host();
	m_port = obj.get_m_port();
	m_fd = obj.get_m_fd();
	m_max_fd = obj.get_m_max_fd();
	m_read_set = obj.get_m_read_set();
	m_read_copy_set = obj.get_m_read_copy_set();
	m_write_set = obj.get_m_write_set();
	m_write_copy_set = obj.get_m_write_copy_set();
	m_servers = obj.get_m_servers();
	m_connections = obj.get_m_connections();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const ProxyBase& server)
{
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

ServerManager* ProxyBase::get_m_manager() const { return (get_m_manager); }
ProxyBase::ProxyType ProxyBase::get_m_type() const { return (m_type); }
const std::string& ProxyBase::get_m_host() const { return (m_host); }
int ProxyBase::get_m_port() const { return (m_port); }
int ProxyBase::get_m_fd() const { return (m_fd); }
int ProxyBase::get_m_max_fd() const { return (m_max_fd); }
fd_set ProxyBase::get_m_read_set() const { return (m_read_set); }
fd_set ProxyBase::get_m_read_copy_set() const { return (m_read_copy_set); }
fd_set ProxyBase::get_m_write_set() const { return (m_write_set); }
fd_set ProxyBase::get_m_write_copy_set() const { return (m_write_copy_set); }
const std::multimap<std::string, int>& ProxyBase::get_m_servers() const { return (m_servers); }
const std::map<int, Connection>& ProxyBase::get_m_connections() const { return (m_connections); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void ProxyBase::set_m_max_fd(int new_max_fd) { m_max_fd = new_max_fd; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ----------------------------- SEND OPERATION ----------------------------- */
/* ************************************************************************** */

bool
ProxyBase::hasSendWorkToClient(Connection& connection)
{

}

bool
ProxyBase::runSendToClient(Connection& connection)
{

}

bool
ProxyBase::hasSendWorkToServer(Connection& connection)
{

}

bool
ProxyBase::runSendToServer(Connection& connection)
{

}

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

bool
ProxyBase::hasRecvWorkFromServer(Connection& connection)
{

}

bool
ProxyBase::runRecvFromServer(Connection& connection)
{

}

bool
ProxyBase::hasRecvWorkFromClient(Connection& connection)
{

}

bool
ProxyBase::runRecvFromClient(Connection& connection)
{

}

/* ************************************************************************** */
/* ----------------------------- PROXY OPERATION ---------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* -------------------------- CONNECTION MANAGEMENT ------------------------- */
/* ************************************************************************** */

bool
ProxyBase::hasNewConnection()
{

}

int
ProxyBase::getUnusedConnectionFd()
{

}

void
ProxyBase::closeConnection(int client_fd)
{

}

bool
ProxyBase::acceptNewConnection()
{

}

void
ProxyBase::closeOldConnection()
{

}	

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
ProxyBase::run()
{
	std::map<int, Connection>::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		std::map<int, Connection>::iterator it2 = it++;
		int fd = it2->first;
		Connection& connection = it2->second;

		if (m_fd == fd)
			continue ;
		if (hasSendWorkToClient(connection) && !runSendToClient(connection))
			continue ;
		if (hasRecvWorkFromServer(connection) && !runRecvFromServer(connection))
			continue ;
		if (hasSendWorkToServer(connection) && !runSendToServer(connection))
			continue ;
		if (hasRecvWorkFromClient(connection))
			runRecvFromClient(connection);
		if (!(connection.get_m_rbuf_from_client().empty()))
			runProxyAction();
	}
	if (hasNewConnection())
	{
		if (m_connections.size() >= 512)
		{
			int fd = getUnusedConnectionFd();
			if (fd == -1)
				return ;
			closeConnection(fd);
		}
		if (!acceptNewConnection())
			reportCreateNewConnectionLog();
	}
}

void
ProxyBase::runProxy()
{

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	while (true)
	{
		int cnt;
		m_manager->fdCopy(ServerManager::ALL_SET);
		
		if ((cnt = select(this->m_max_fd + 1, &this->m_read_copy_set, &this->m_write_copy_set, \
		NULL, &timeout)) == -1)
			ft::log(ServerManager::access_fd, ServerManager::error_fd, "[Failed][Function]Select function failed(return -1)");
			throw std::runtime_error("select error");
		else if (cnt == 0)
			continue ;
		writeProxyHealthLog();
		run();
		closeOldConnection();
	}
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
ProxyBase::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{

}

void
ProxyBase::reportCreateNewConnectionLog()
{

}

void
ProxyBase::writeProxyHealthLog()
{

}

void
ProxyBase::writeCloseConnectionLog(int client_fd)
{
	
}
