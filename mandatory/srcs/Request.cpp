/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jujengim <jujengim@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:42:05 by yopark            #+#    #+#             */
/*   Updated: 2020/10/02 22:09:14 by jujeng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "ServerManager.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Request::Request()
{
	m_phase = READY;
	m_connection = NULL;
	m_server = NULL;
	m_location = NULL;
	m_start_at.tv_sec = 0;
	m_start_at.tv_usec = 0;
	m_phase = READY;
	m_method = DEFAULT;
	m_uri_type = FILE;
	m_special_header_count = 0;
	m_transfer_type = GENERAL;
}

bool
Request::parseMethod(std::string methodString)
{
	if (methodString == "GET")
		m_method = GET;
	else if (methodString == "HEAD")
		m_method = HEAD;
	else if (methodString == "POST")
		m_method = POST;
	else if (methodString == "PUT")
		m_method = PUT;
	else if (methodString == "DELETE")
		m_method = DELETE;
	else if (methodString == "OPTIONS")
		m_method = OPTIONS;
	else if (methodString == "TRACE")
		m_method = TRACE;
	else
		return (false);
	return (true);
}

bool
Request::assignLocationMatchingUri(std::string uri)
{
	size_t max_uri_match = 0;
	for (std::vector<Location>::const_iterator it = m_server->get_m_locations().begin() ; it != m_server->get_m_locations().end() ; ++it)
	{
		if (std::strncmp(it->get_m_uri().c_str(), uri.c_str(), it->get_m_uri().length()) == 0 && it->get_m_uri().length() > max_uri_match)
		{
			m_location = const_cast<Location *>(&(*it));
			max_uri_match = it->get_m_uri().length();
		}
	}
	if (!max_uri_match)
		return (false);
	return (true);
}

namespace {
	std::string getTranslatedPath(std::string root, std::string uri)
	{
		if (uri.empty())
			return (root);
		if (root[root.size() - 1] == '/' && uri[0] == '/')
			uri.erase(uri.begin());
		else if (root[root.size() - 1] != '/' && uri[0] != '/')
			uri.insert(0, 1, '/');
		return (root + uri);
	}
}

namespace {
	std::string getIndexPath(const std::set<std::string>& index_set, std::string base_path)
	{
		std::set<std::string>::const_iterator it = index_set.begin();
		struct stat buf;
		std::string path;
		for (; it != index_set.end(); ++it)
		{
			path = getTranslatedPath(base_path, *it);
			stat(path.c_str(), &buf);
			if (S_ISREG(buf.st_mode))
				return (*it);
		}
		return ("");
	}
}

std::string
Request::parseUri()
{
	std::string root = m_location->get_m_uri();
	std::string uri = (root == "/") ? m_uri : m_uri.substr(m_uri.find(root) + root.size());
	std::string main_path = uri;
	std::string refer_path = uri;

	if (ft::isDirectory(getTranslatedPath(m_location->get_m_root_path(), uri)) && !m_location->get_m_autoindex())
		uri = m_uri = getIndexPath(get_m_location()->get_m_index(), getTranslatedPath(m_location->get_m_root_path(), uri));
	for (std::set<std::string>::const_iterator it = m_location->get_m_cgi().begin() ; it != m_location->get_m_cgi().end() ; ++it)
	{
		if (uri.find(*it) != std::string::npos)
		{
			int idx = uri.find(*it);
			m_uri_type = CGI_PROGRAM;
			if ((m_method == GET || m_method == HEAD) && uri.find("?") != std::string::npos) {
				m_query = uri.substr(uri.find("?") + 1);
				uri = uri.substr(0, uri.find("?"));
				m_path_info = m_uri.substr(0, uri.find("?"));
			} else
				m_path_info = m_uri;
			main_path = uri.substr(0, idx + it->size());
			refer_path = uri.substr(idx + it->size());
			break ;
		}
	}
	m_script_translated = getTranslatedPath(m_location->get_m_root_path(), main_path);
	m_path_translated = getTranslatedPath(m_location->get_m_root_path(), refer_path);
	if (m_uri_type == CGI_PROGRAM && !ft::isFile(m_script_translated))
	{
		if (!m_location->get_m_index().empty())
		{
			m_method = Request::GET;
			m_uri = m_location->get_m_uri();
			m_script_translated = m_location->get_m_root_path();
		}
		else
			throw (40404);
	}
	return (m_script_translated);
}

Request::Request(Connection *connection, Server *server, std::string start_line)
: m_connection(connection), m_server(server), m_transfer_type(GENERAL)
{
	m_phase = ON_HEADER;
	if (gettimeofday(&m_start_at, NULL) == -1)
		throw std::runtime_error("gettimeofday function failed in request generator");

	std::vector<std::string> parsed = ft::split(start_line, ' ');
	if (parsed.size() != 3) {
		ft::log(ServerManager::access_fd, ServerManager::error_fd, "[StartLine]" + start_line);
		throw (40000);
	}
	if (!parseMethod(parsed[0]))
		throw (40001);
	if (parsed[1].length() > m_server->get_m_request_uri_limit_size())
		throw (41401);

	m_uri = parsed[1];
	if (!(assignLocationMatchingUri(m_uri)))
		throw (40401);
	std::string translated_path = parseUri();
	if (translated_path.empty())
		throw (40002);
	if (ft::isFile(translated_path) && m_uri_type != CGI_PROGRAM)
		m_uri_type = FILE;
	else if (ft::isDirectory(translated_path))
		m_uri_type = DIRECTORY;
	else if (m_method == PUT || m_method == TRACE)
		m_uri_type = FILE_TO_CREATE;
	else if (m_uri_type != CGI_PROGRAM)
		throw (40402);
	if ((m_protocol = parsed[2]) != "HTTP/1.1")
		throw (50501);
	m_special_header_count = 0;
}

Request::Request(const Request &x)
{
	m_connection = x.m_connection;
	m_server = x.m_server;
	m_location = x.m_location;
	m_start_at = x.m_start_at;

	m_method = x.m_method;
	m_phase = x.m_phase;
	m_uri = x.m_uri;
	m_uri_type = x.m_uri_type;
	m_protocol = x.m_protocol;
	m_headers = x.m_headers;
	m_transfer_type = x.m_transfer_type;
	m_content = x.m_content;
	m_query = x.m_query;
	m_path_translated = x.m_path_translated;
	m_script_translated = x.m_script_translated;
	m_path_info = x.m_path_info;
	m_origin = x.m_origin;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Request::~Request()
{
	m_connection = NULL;
	m_server = NULL;
	m_location = NULL;
	m_phase = READY;
	m_start_at.tv_sec = 0;
	m_start_at.tv_usec = 0;

	m_uri.clear();
	m_protocol.clear();
	m_headers.clear();
	m_content.clear();
	m_query.clear();
	m_path_translated.clear();
	m_script_translated.clear();
	m_path_info.clear();
	m_origin.clear();
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
	m_phase = x.m_phase;
	m_method = x.m_method;
	m_uri = x.m_uri;
	m_uri_type = x.m_uri_type;
	m_protocol = x.m_protocol;
	m_headers = x.m_headers;
	m_transfer_type = x.m_transfer_type;
	m_content = x.m_content;
	m_query = x.m_query;
	m_path_translated = x.m_path_translated;
	m_script_translated = x.m_script_translated;
	m_path_info = x.m_path_info;
	m_origin = x.m_origin;

	return (*this);
}

std::ostream &operator<<(std::ostream &out, const Request &request)
{
	out << "METHOD: " << request.get_m_method() << " (GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE)" << std::endl;
	out << "URI: " << request.get_m_uri() << std::endl;
	out << "URI_TYPE: " << request.get_m_uri_type() << " (DIRECTORY, FILE, CGI_PROGRAM)" << std::endl;
	out << "PROTOCOL: " << request.get_m_protocol() << std::endl;
	out << "headers_t:" << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = request.get_m_headers().begin() ; it != request.get_m_headers().end() ; ++it)
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
const std::string		&Request::get_m_query() const { return (m_query); }
const std::string		&Request::get_m_path_info() const { return (m_path_info); }
const std::string		&Request::get_m_origin() const { return (m_origin); }
const std::string		&Request::get_m_path_translated() const { return (m_path_translated); }
const std::string		&Request::get_m_script_translated() const { return (m_script_translated); }
std::string 			Request::get_m_method_to_string() const
{
	if (m_method == GET) return (std::string("GET"));
	else if (m_method == HEAD) return (std::string("HEAD"));
	else if (m_method == POST) return (std::string("POST"));
	else if (m_method == PUT) return (std::string("PUT"));
	else if (m_method == DELETE) return (std::string("DELETE"));
	else if (m_method == TRACE) return (std::string("TRACE"));
	else if (m_method == OPTIONS) return (std::string("OPTIONS"));
	return (std::string(""));
}
Request::Phase			Request::get_m_phase() const { return (m_phase); }
int						Request::get_m_special_header_count() const { return (m_special_header_count); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Request::addContent(std::string added_content)
{
	if (m_content.size() + added_content.size() > m_location->get_m_limit_client_body_size())
		throw (41301);
	m_content.append(added_content);
}

void Request::addOrigin(std::string added_origin, bool limit_ignore)
{
	if (limit_ignore && m_method != TRACE)
		return ;
	if (limit_ignore && m_origin.size() + added_origin.size() > m_server->get_m_limit_client_body_size())
		throw (41302);
	m_origin.append(added_origin);
}

void Request::addHeader(std::string header)
{
	size_t pos = header.find(':');
	std::string key = ft::trim(header.substr(0, pos));
	std::string value = ft::trim(header.substr(pos + 1));
	for (size_t i = 0 ; i < key.length() ; ++i)
		key[i] = (i == 0 || key[i - 1] == '-') ? std::toupper(key[i]) : std::tolower(key[i]);

	std::pair<std::map<std::string, std::string>::iterator, bool> ret = m_headers.insert(std::make_pair(key, value));
	if (!ret.second)
		throw (40003);

	if (key == "Transfer-Encoding" && value.find("chunked") != std::string::npos)
		m_transfer_type = CHUNKED;
	if (key == "Content-Length")
	{
		int content_length = ft::stoi(value);
		if (content_length > static_cast<int>(m_server->get_m_limit_client_body_size()))
			throw (41303);
		if (content_length < 0)
			throw (40004);
	}
	if (key[0] == 'X')
		++m_special_header_count;
	return ;
}

void Request::set_m_phase(Phase phase) { m_phase = phase; }
void Request::set_m_method(Method method) { m_method = method; }
void Request::set_m_transfer_type(TransferType transfer_type) { m_transfer_type = transfer_type; }
void Request::addSpecialHeaderCount() { ++m_special_header_count; }

void Request::clear()
{
	m_phase = READY;
	m_method = DEFAULT;
	m_uri.clear();
	m_uri_type = FILE;
	m_protocol.clear();
	m_headers.clear();
	m_special_header_count = 0;
	m_transfer_type = GENERAL;
	m_content.clear();
	m_query.clear();
	m_script_translated.clear();
	m_path_translated.clear();
	m_path_info.clear();
	m_origin.clear();
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
		throw (40005);
	if (header.find(":") == std::string::npos)
		return (false);
	return (true);
}

bool Request::isOverTime() const
{
	timeval now;

	if (gettimeofday(&now, NULL) == -1)
		throw std::runtime_error("gettimeofday error");

	long now_nbr = now.tv_sec + now.tv_usec / 1000000;
	long start_nbr = m_start_at.tv_sec + m_start_at.tv_usec / 1000000;

	return ((now_nbr - start_nbr) >= REQUEST_TIMEOVER_SECOND);
}
