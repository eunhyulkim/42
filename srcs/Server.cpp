#include "Server.hpp"

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
	m_port = std::stoi(server_map["port"]);
	m_request_uri_limit_size = std::stoi(server_map["REQUEST_URI_LIMIT_SIZE"]);
	m_request_header_limit_size = std::stoi(server_map["REQUEST_HEADER_LIMIT_SIZE"]);
	m_limit_client_body_size = std::stoi(server_map["LIMIT_CLIENT_BODY_SIZE"]);
	m_default_error_page = ft::getStringFromFile(server_map["DEFAULT_ERROR_PAGE"]);

	//socket 생성
	if((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("SOCKET ERROR");
	int value = true;
	if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
	server_addr.sin_port = htons(m_port);
	if(bind(m_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(struct sockaddr)) == -1)
		throw std::runtime_error("BIND ERROR");
	if(listen(m_fd, 64) == -1)
		throw std::runtime_error("LISTEN ERROR");
	if (fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("FCNTL ERROR");
	m_manager->fdSet(m_fd, ServerManager::SetType::READ_SET);
	if (m_manager->m_max_fd < m_fd)
		m_manager->m_max_fd = m_fd;

	for (std::vector<std::string>::iterator it = location_blocks.begin(); it != location_blocks.end(); ++it)
	{
		uri = ft::split(ft::split(*it).front(), ' ')[1];
		block = *it;
		block = block.substr(block.find('\n') + 1);
		m_locations.push_back(Location(uri, block));
	}
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
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::~Server()
{
	close(m_fd);
}

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
	/* overload= code */
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
int Server::get_m_request_uri_limit_size() const { return (this->m_request_uri_limit_size); }
int Server::get_m_request_header_limit_size() const { return (this->m_request_header_limit_size); }
int Server::get_m_limit_client_body_size() const { return (this->m_limit_client_body_size); }
const std::string& Server::get_m_default_error_page() const { return (this->m_default_error_page); }
Config* Server::get_m_config() const { return (this->m_config); }
const std::vector<Location>& Server::get_m_locations() const { return (this->m_locations); }
const std::map<int, Connection>& Server::get_m_connections() const { return (this->m_connections); }
const std::queue<Response>& Server::get_m_responses() const { return (this->m_responses); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

// void Server::set_m_server_name(std::string server_name) { this->m_server_name = server_name; }
// void Server::set_m_host(std::string host) { this->m_host = host; }
// void Server::set_m_port(int port) { this->m_port = port; }
// void Server::set_m_fd(int fd) { this->m_fd = fd; }
// void Server::set_m_request_uri_limit_size(int request_uri_limit_size) { this->m_request_uri_limit_size = request_uri_limit_size; }
// void Server::set_m_request_header_limit_size(int request_header_limit_size) { this->m_request_header_limit_size = request_header_limit_size; }
// void Server::set_m_limit_client_body_size(int limit_client_body_size) { this->m_limit_client_body_size = limit_client_body_size; }
// void Server::set_m_default_error_page(std::string default_error_page) { this->m_default_error_page = default_error_page; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

/*
** function: solveRequest
** 1. check request method is allowed
** 2. Check authentication is required
** 2. If uri is directory, check reqeust method is GET(if not, response 405)
** 3. if uri is directory(with GET method), executeAutoindex
*/

void base64_decode(std::string data, std::string& key, std::string& value)
{

}

void
Server::solveRequest(const Request& request)
{
	Location* location = request.get_m_location();
	std::string method = request.get_m_method_to_string();

	if (!ft::hasKey(location->get_m_allow_method(), method)) {
		createResponse(405, ft::setToString(location->get_m_allow_method(), " "));
		return ;
	}
	if (!location->get_m_auth_basic_realm().empty()) {
		if (!ft::hasKey(request.get_m_headers(), "Authorization")) {
			createResponse(401, location->get_m_auth_basic_realm());
		} else {
			std::vector<std::string> credential = ft::split(request.get_m_headers().find("Authorization")->second, ' ');
			if (credential.size() != 2 || credential[0] != "basic") {
				return (createReponse(400));
			}
			else {
				std::string key, value;
				base64_decode(credential[1], key, value);
				if (!ft::hasKey(location->get_m_auth_basic_file(), key)
				|| location->get_m_auth_basic_file()[key] != value) {
					return (createResponse(403));
				}
			}
		}
	}
	if (request.get_m_uri_type() == Request::URIType::DIRECTORY)
		executeAutoindex();
	Request::Method method = request.get_m_method();
	if (method == Request::Method::GET)
		executeGet(request);
	else if (method == Request::Method::HEAD)
		executeHead(request);
	else if (method == Request::Method::POST)
		executePost(request);
	else if (method == Request::Method::PUT)
		executePut(request);
	else if (method == Request::Method::DELETE)
		executeDelete(request);
	else if (method == Request::Method::OPTIONS)
		executeOptions(request);
	else if (method == Request::Method::TRACE)
		executeTrace(request);
}

std::string
Server::inet_ntoa(unsigned int address)
{
	std::string ret;

	ret = std::to_string(address & 0xFF) + ".";
	ret.append(std::to_string((address >> 8) & 0xFF) + ".");
	ret.append(std::to_string((address >> 16) & 0xFF) + ".");
	ret.append(std::to_string((address >> 24) & 0xFF));
	return (ret);
}

bool
Server::hasException(int client_fd) {
	return (m_manager->fdIsset(client_fd, ServerManager::SetType::ERROR_COPY_SET));
}

void
Server::closeConnection(int client_fd)
{
	close(client_fd);
	m_manager->fdClear(client_fd, ServerManager::SetType::READ_SET);
	m_connections.erase(client_fd);
}

bool
Server::hasNewConnection()
{
	return (m_manager->fdIsset(m_fd, ServerManager::SetType::READ_COPY_SET))
}

void
Server::acceptNewConnection()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size = sizeof(struct sockaddr_in);
	int 				client_fd;
	std::string			client_ip;
	int					client_port;

	ft::bzero(&client_addr, client_addr_size);

	if ((client_fd = accept(m_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
		return ;
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return ;
	client_ip = inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	m_manager->fdSet(client_fd, ServerManager::SetType::READ_SET);

	return ;
}

void
Server::run()
{
	int response_count = 0;
	while (!m_responses.empty() || response_count < SEND_RESPONSE_AT_ONCE)
	{
		++response_count;
		Response response(m_responses.front());
		m_responses.pop();
		if (isSendable(response.get_m_connection()->get_m_client_fd()))
			sendResponse(response);
		if (response.get_m_connection_type() == Response::ConnectionType::CLOSE)
			closeConnection(response.get_m_connection()->get_m_client_fd());
	}

	std::map<int, Connection>::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		Request request;
		int fd = it->first;

		++it;
		if (hasException(fd)) {
			closeConnection(fd);
			continue ;
		}
		if (hasRequest(fd))	{
			try {
				request = recvRequest(fd, it->second);
			} catch (int status_code) {
				createResponse(status_code);
				continue ;
			} catch (std::exception& e) {
				createResponse(500);
				continue ;
			}
			if (m_responses.size() > RESPONSE_OVERLOAD_COUNT) {
				createResponse(503, "60");
				closeConnection(fd);
				continue ;
			}
			solveRequest(request);
		}
	}

	if (hasNewConnection())
	{
		if (m_connections.size() >= (1024 / m_manager->m_servers.size()))
		{
			std::map<int, Connection>::iterator it = m_connections.begin();
			for (; it != m_connections.end(); ++it) {
				if (!m_manager->fdIsset(it->first, ServerManager::SetType::WRITE_SET))
					break ;
			}
			if (it == m_connections.end())
				return ;
			closeConnection(it->first);
		}
		acceptNewConnection();
	}
}

// int Server::isSendable(int client_fd){}
// int Server::sendResponse(Response response){}

bool Server::hasRequest(int client_fd)
{
	return (m_manager->fdIsset(client_fd, ServerManager::SetType::READ_COPY_SET));
}

Request Server::recvRequest(int client_fd, Connection connection)
{
	enum TransferType { GENERAL, CHUNKED };
	ssize_t		read_len = 0;
	ssize_t		total_read_len = 0;
	char		buffer[1024];
	std::string	origin_message;
	std::string start_line;
	std::string message_body;
	std::string buf;
	TransferType transfer_type = GENERAL;
	int header_size = 0;
	int content_length = 0;
	bool host_header = false;

	dup2(client_fd, 0);
	std::getline(std::cin, start_line);
	start_line = ft::rtrim(start_line, "\r");
	Request request(&connection, this, start_line);
	while (!std::cin.eof()) //header parsing
	{
		std::getline(std::cin, buf);
		if (buf == "\r" || buf == "")
			break;
		if (!request.isValidHeader(buf))
			throw (400);
		buf = ft::rtrim(buf, "\r");
		size_t pos = buf.find(':');
		std::string key = ft::trim(buf.substr(0, pos));
		std::string value = ft::trim(buf.substr(pos + 1));
		for (size_t i = 0 ; i < key.length() ; ++i) // capitalize
			key[i] = (i == 0 || key[i - 1] == '-') ? std::toupper(key[i]) : std::tolower(key[i]);
		if (key == "Content-Type" && value.find("chunked") != std::string::npos)
			transfer_type = CHUNKED;
		if (key == "Content-Length")
		{
			content_length = std::stoi(value);
			if (content_length > this->m_limit_client_body_size)
				throw (413);
		}
		if (key == "Host")
			host_header = true;
		// std::cout << buf << std::endl;
		request.add_header(key, value);
	}
	if (!host_header)
		throw 400;
	if (request.get_m_method() == Request::Method::POST || request.get_m_method() == Request::Method::PUT)
	{
		if (transfer_type == CHUNKED)
		{
			std::getline(std::cin, buf);
			origin_message = buf + "\n";
			buf = ft::rtrim(buf, "\r");
			if (content_length)
				throw 400;
			content_length = std::stoi(buf);
		}
		if (content_length < 0)
			throw 400;
		if (content_length > 0)
		{
			while ((read_len = read(client_fd, buffer, 1024)) != -1)
			{
				message_body.append(buf, read_len);
				total_read_len += read_len;
				if (total_read_len >= content_length)
					break;
			}
		}
	}
	else
	{
		if ((read_len = read(client_fd, buffer, 1024)) != -1)
			throw 400;
	}
	origin_message += message_body;
	request.add_content(message_body);
	if (request.get_m_method() == Request::Method::TRACE)
		request.add_origin(origin_message);
	return (request);
}

// void executeAutoindex(const Request& request);
// int Server::executeGet(Request request){}
// int Server::executeHead(Request request){}
// int Server::executePut(Request request){}
// int Server::executePost(Request request){}
// int Server::executeDelete(Request request){}
// int Server::executeOptions(Request request){}
// int Server::executeTrace(Request request){}

// char** Server::createCGIEnv(Request request){}
// int Server::executeCGI(Request request){}

// int Server::createResponse(int status){}
