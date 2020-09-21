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

/*
** function: solveRequest
** 1. check request method is allowed
** 2. Check authentication is required
** 2. If uri is directory, check reqeust method is GET(if not, response 405)
** 3. if uri is directory(with GET method), executeAutoindex 
*/

void base64_decode(std::string data, std::string& key, std::string& value)
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
