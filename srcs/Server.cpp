#include "Server.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::Server() {}
Server::Server(const std::string& server_block, const std::string& location_blocks)
: 
{
	this->m_server_name.clear();
	this->m_host.clear();
	this->m_port = 0;
	this->m_fd = 0;
	this->m_request_uri_limit_size = 0;
	this->m_request_header_limit_size = 0;
	this->m_limit_client_body_size = 0;
	this->m_default_error_page.clear();
}

Server::Server(const Server& copy)
: 
{
	this->m_server_name.clear();
	this->m_host.clear();
	this->m_port = 0;
	this->m_fd = 0;
	this->m_request_uri_limit_size = 0;
	this->m_request_header_limit_size = 0;
	this->m_limit_client_body_size = 0;
	this->m_default_error_page.clear();
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::~Server()
{
	this->m_server_name.clear();
	this->m_host.clear();
	this->m_port = 0;
	this->m_fd = 0;
	this->m_request_uri_limit_size = 0;
	this->m_request_header_limit_size = 0;
	this->m_limit_client_body_size = 0;
	this->m_default_error_page.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Server& Server::operator=(const Server& obj)
{
	if (this == &obj)
		return (*this);
	this->m_server_name = obj.get_m_server_name();
	this->m_host = obj.get_m_host();
	this->m_port = obj.get_m_port();
	this->m_fd = obj.get_m_fd();
	this->m_request_uri_limit_size = obj.get_m_request_uri_limit_size();
	this->m_request_header_limit_size = obj.get_m_request_header_limit_size();
	this->m_limit_client_body_size = obj.get_m_limit_client_body_size();
	this->m_default_error_page = obj.get_m_default_error_page();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Server& server)
{
	out << "" << server.get_m_server_name();
	out << "" << server.get_m_host();
	out << "" << server.get_m_port();
	out << "" << server.get_m_fd();
	out << "" << server.get_m_request_uri_limit_size();
	out << "" << server.get_m_request_header_limit_size();
	out << "" << server.get_m_limit_client_body_size();
	out << "" << server.get_m_default_error_page();
	out << "" << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Server::get_m_server_name() const { return (this->m_server_name); }
std::string Server::get_m_host() const { return (this->m_host); }
int Server::get_m_port() const { return (this->m_port); }
int Server::get_m_fd() const { return (this->m_fd); }
int Server::get_m_request_uri_limit_size() const { return (this->m_request_uri_limit_size); }
int Server::get_m_request_header_limit_size() const { return (this->m_request_header_limit_size); }
int Server::get_m_limit_client_body_size() const { return (this->m_limit_client_body_size); }
std::string Server::get_m_default_error_page() const { return (this->m_default_error_page); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Server::set_m_server_name(std::string server_name) { this->m_server_name = server_name; }
void Server::set_m_host(std::string host) { this->m_host = host; }
void Server::set_m_port(int port) { this->m_port = port; }
void Server::set_m_fd(int fd) { this->m_fd = fd; }
void Server::set_m_request_uri_limit_size(int request_uri_limit_size) { this->m_request_uri_limit_size = request_uri_limit_size; }
void Server::set_m_request_header_limit_size(int request_header_limit_size) { this->m_request_header_limit_size = request_header_limit_size; }
void Server::set_m_limit_client_body_size(int limit_client_body_size) { this->m_limit_client_body_size = limit_client_body_size; }
void Server::set_m_default_error_page(std::string default_error_page) { this->m_default_error_page = default_error_page; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool
Server::hasException(int client_fd) {
	return (m_manager->fdIsset(client_fd, ServerManager::SetType::ERROR_COPY_SET))
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
	client_ip = ft::inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	m_manager->fdSet(client_fd, ServerManager::SetType::READ_SET);
	return ;
}

