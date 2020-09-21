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
	error_page = server_map["DEFAULT_ERROR_PAGE"];
	//socket 생성
	if((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("SOCKET ERROR");
	int value = true;
	if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(struct sockaddr_in));
	// memset((void *)&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
	server_addr.sin_port = htons(m_port);
	if(bind(m_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(struct sockaddr)) == -1)
		throw std::runtime_error("BIND ERROR");
	if(listen(m_fd, 64) == -1)
		throw std::runtime_error("LISTEN ERROR");
	if (fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("FCNTL ERROR");
	// m_manager->fdSet(m_fd, ServerManager::SetType::READ_SET);
	// if (m_manager->m_max_fd < m_fd)
	// 	m_manager->m_max_fd = m_fd;
	m_default_error_page = ft::getStringFromFile(error_page);
	for (std::vector<std::string>::iterator it = location_blocks.begin(); it != location_blocks.end(); ++it)
	{
		uri = ft::split(ft::split(*it).front(), ' ')[1];
		block = *it;
		block = block.substr(block.find('\n') + 1);
		m_locations.push_back(Location(uri, block));
	}

	// test
	std::cout << m_server_name << std::endl;
	std::cout << m_host << std::endl;
	std::cout << m_port << std::endl;
	std::cout << m_fd << std::endl;
	std::cout << m_request_uri_limit_size << std::endl;
	std::cout << m_request_header_limit_size << std::endl;
	std::cout << m_limit_client_body_size << std::endl;
	std::cout << m_default_error_page << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << m_locations.front() << std::endl;
	std::cout << "------------------" << std::endl;
	// std::cout << m_locations.back() << std::endl;
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
	// out << "" << server.get_m_server_name();
	// out << "" << server.get_m_host();
	// out << "" << server.get_m_port();
	// out << "" << server.get_m_fd();
	// out << "" << server.get_m_request_uri_limit_size();
	// out << "" << server.get_m_request_header_limit_size();
	// out << "" << server.get_m_limit_client_body_size();
	// out << "" << server.get_m_default_error_page();
	// out << "" << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

// std::string Server::get_m_server_name() const { return (this->m_server_name); }
// std::string Server::get_m_host() const { return (this->m_host); }
// int Server::get_m_port() const { return (this->m_port); }
// int Server::get_m_fd() const { return (this->m_fd); }
// int Server::get_m_request_uri_limit_size() const { return (this->m_request_uri_limit_size); }
// int Server::get_m_request_header_limit_size() const { return (this->m_request_header_limit_size); }
// int Server::get_m_limit_client_body_size() const { return (this->m_limit_client_body_size); }
// std::string Server::get_m_default_error_page() const { return (this->m_default_error_page); }

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

// bool Server::hasException(int client_fd){}
// int Server::closeConnection(int client_fd){}
// int Server::isSendable(int client_fd){}
// int Server::sendResponse(Response response){}
// bool Server::hasRequest(int client_fd){}
// Request Server::readRequest(int client_fd){}
// int Server::solveRequest(Request request){}
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
// bool Server::hasNewConnection(){}
// int Server::acceptNewConnection(){}
// int Server::run(){}
