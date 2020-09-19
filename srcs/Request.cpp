/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:42:05 by yopark            #+#    #+#             */
/*   Updated: 2020/09/19 20:57:07 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#include "Server.hpp"
#include "Connection.hpp"
#include "Location.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Request::Request(Connection *connection, Server *server, std::string start_line): m_connection(connection), m_server(server), m_transfer_type(GENERAL)
{
	if (gettimeofday(&m_start_at, NULL) == -1)
		throw std::runtime_error("gettimeofday error");

	std::vector<std::string> parsed = ft::split(start_line, ' ');
	if (parsed.size() != 3) throw 400;
	if (parsed[0] == "GET") m_method = GET;
	else if (parsed[0] == "HEAD") m_method = HEAD;
	else if (parsed[0] == "POST") m_method = POST;
	else if (parsed[0] == "PUT") m_method = PUT;
	else if (parsed[0] == "DELETE") m_method = DELETE;
	else if (parsed[0] == "OPTIONS") m_method = OPTIONS;
	else if (parsed[0] == "TRACE") m_method = TRACE;
	else throw 400;
	if (m_location->get_m_allow_method().find(parsed[0]) == m_location->get_m_allow_method().end())
		throw 405;

	if (parsed[1].length() > m_server->get_m_request_uri_limit_size())
		throw 414;
	m_uri = parsed[1];
	int max_uri_match = 0;
	for (it = m_server->get_m_locations()->begin() ; it != m_server->get_m_locations()->end() ; ++it)
	{
		if (std::strncmp((*it)->get_m_uri(), m_uri, (*it)->get_m_uri().length()) == 0 && (*it)->get_m_uri().length() > max_uri_match)
		{
			m_location = it;
			max_uri_match = (*it)->get_m_uri().length();
		}
	}
	if (!max_uri_match)
		throw 404;	
	std::string path(m_location->get_m_root_path() + m_uri);
	struct stat buf;
	stat(path.c_str(), &buf);
	m_uri_type = FILE;
	if (S_ISREG(buf.st_mode))
	{
		for (std::set<std::string>::const_iterator it = m_location->get_m_cgi().begin() ; it != m_location->get_m_cgi().end() ; ++it)
		{
			if (path.find(*it, path.length() - (*it).length()) != std::string::npos)
				m_uri_type = CGI_PROGRAM;
		}
	}
	else if (S_ISDIR(buf.st_mode)) m_uri_type = DIRECTORY;
	else throw 404;

	m_protocol = parsed[2];
	if (m_protocol != "HTTP/1.1")
		throw 505;
}

Request::Request(const Request &x)
{
	m_connection = x.m_connection;
	m_server = x.m_server;
	m_location = x.m_location;
	m_start_at = x.m_start_at;

	m_method = x.m_method;
	m_uri = x.m_uri;
	m_uri_type = x.m_uri_type;
	m_protocol = x.m_protocol;
	m_headers = x.m_headers;
	m_transfer_type = x.m_transfer_type;
	m_content = x.m_content;
	m_origin = x.m_origin;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Request::~Request()
{

}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Request &Request::operator=(const Request &x)
{
	if (this == &x)
		return (*this);

	m_connection = x.m_connection;
	m_server = x.m_server;
	m_location = x.m_location;
	m_start_at = x.m_start_at;

	m_method = x.m_method;
	m_uri = x.m_uri;
	m_uri_type = x.m_uri_type;
	m_protocol = x.m_protocol;
	m_headers = x.m_headers;
	m_transfer_type = x.m_transfer_type;
	m_content = x.m_content;
	m_origin = x.m_origin;

	return (*this);
}

std::ostream &operator<<(std::ostream &out, const Request &request)
{
	out << "METHOD: " << request.get_m_method() << " (GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE)" << std::endl;
	out << "URI: " << request.get_m_uri() << std::endl;
	out << "URI_TYPE: " << request.get_m_uri_type() << " (DIRECTORY, FILE, CGI_PROGRAM)" << std::endl;
	out << "PROTOCOL: " << request.get_m_protocol() << std::endl;
	out << "HEADERS:" << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = request.get_m_headers().begin() ; it != request.get_m_headers().end() ; ++it) // mapToString
		out << "KEY: " << (*it).first << ", " << "VALUE: " << (*it).second << std::endl;
	out << "TRANSFER_TYPE: " << request.get_m_transfer_type() << " (GENERAL, CHUNKED)" << std::endl;
	out << "CONTENT: " << request.get_m_content() << std::endl;
	out << "ORIGIN: " << request.get_m_origin() << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

Connection				*Request::get_m_connection() const { return (m_connection); }
Server					*Request::get_m_server() const { return (m_server); }
Location				*Request::get_m_location() const { return (m_location); }
Request::Method			Request::get_m_method() const { return (m_method); }
const std::string		&Request::get_m_uri() const { return (m_uri); }
Request::URIType		Request::get_m_uri_type() const { return (m_uri_type); }
const std::string		&Request::get_m_protocol() const { return (m_protocol); }
const std::map<std::string, std::string> &Request::get_m_headers() const { return (m_headers); }
Request::TransferType	Request::get_m_transfer_type() const { return (m_transfer_type); }
const std::string		&Request::get_m_content() const { return (m_content); }
const std::string		&Request::get_m_origin() const { return (m_origin); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Request::add_content(std::string added_content)
{
	m_content.append(added_content);
}

void Request::add_origin(std::string added_origin)
{
	m_origin.append(added_origin);
}


void Request::add_header(std::string header)
{
	size_t pos = header.find(':');
	std::string key = header.substr(0, pos);
	std::string value = header.substr(pos + 1);
	key = ft::trim(key);
	value = ft::trim(value);
	for (size_t i = 0 ; i < key.length() ; ++i) // capitalize
		key[i] = (i == 0 || key[i - 1] == '-') ? std::toupper(key[i]) : std::tolower(key[i]);

	if (key == "Content-Type" && value == "chunked")
		m_transfer_type = CHUNKED;
	if (key == "Content-Length" && std::atoi(value.c_str()) > m_server->get_m_limit_client_body_size())
		throw 413;
	std::pair<std::map<std::string, std::string>::iterator, bool> ret = m_headers.insert(std::make_pair(key, value));
	if (!ret.second)
		throw 400;
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool Request::isValidHeader(std::string header)
{
	if (header.size() > m_server->get_m_request_header_limit_size())
		throw 400;
	if (header.find(':') == std::string::npos)
		return (false);
	return (true);
}

bool Request::isOverTime()
{
	timeval now;

	if (gettimeofday(&now, NULL) == -1)
		throw std::runtime_error("gettimeofday error");
	
	long now_nbr = now.tv_sec * 1000 + now.tv_usec;
	long start_nbr = m_start_at.tv_sec * 1000 + m_start_at.tv_usec;
	
	return ((now_nbr - start_nbr) / 1000 >= REQUEST_TIMEOVER);
}
