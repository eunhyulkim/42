/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 02:56:35 by yopark            #+#    #+#             */
/*   Updated: 2020/09/18 16:53:50 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <sys/time.h> // gettimeofday
#include <sys/stat.h> // stat

#define TIMEOVER 42
#define REQUEST_URI_LIMIT_SIZE 1024
#define REQUEST_HEADER_LIMIT_SIZE 256
#define REQUEST_BODY_LIMIT_SIZE 8192

#define TMP_ROOT "/Users/yopark/Desktop/webserv/eunhkim" // m_location.m_root으로 대체
#define TMP_CGI ".php" // m_location.m_cgi으로 대체

namespace ft
{
	std::vector<std::string> split(std::string s, char c)
	{
		std::vector<std::string> ret;
		size_t pos = 0;

		while ((pos = s.find(c)) != std::string::npos)
		{
			if (pos != 0)
				ret.push_back(s.substr(0, pos));
			s.erase(0, pos + 1);
		}
		if (s.length() != 0)
			ret.push_back(s);
		return (ret);
	}
}

void Request::add_content(std::string added_content)
{
	m_content.append(added_content);
}

void Request::add_origin(std::string added_origin)
{
	m_origin.append(added_origin);
}

#define SPACE_CHARSET " \t\n\r\f\v"

void Request::add_header(std::string header)
{
	size_t pos = header.find(':');
	std::string key = header.substr(0, pos);
	std::string value = header.substr(pos + 1);

	key.erase(key.find_last_not_of(SPACE_CHARSET) + 1);
	for (size_t i = 0 ; i < key.length() ; ++i) // capitalize
		key[i] = (i == 0 || key[i - 1] == '-') ? std::toupper(key[i]) : std::tolower(key[i]);
	value.erase(0, value.find_first_not_of(SPACE_CHARSET));
	value.erase(value.find_last_not_of(SPACE_CHARSET) + 1);

	// value의 대소문자 구분 알아보기

	if (key == "Content-Type" && value == "chunked")
		m_transfer_type = CHUNKED;
	if (key == "Content-Length" && std::atoi(value.c_str()) > REQUEST_BODY_LIMIT_SIZE)
		throw "413 Payload Too Large";
	std::pair<std::map<std::string, std::string>::iterator, bool> ret = m_headers.insert(std::make_pair(key, value));
	if (!ret.second)
		throw "400 Bad Request"; // 중복 키
}

bool Request::isValidHeader(std::string header)
{
	if (header.find(':') == std::string::npos)
		return (false);
	if (header.size() > REQUEST_HEADER_LIMIT_SIZE)
		throw "400 Bad Request";
	return (true); // 이 조건 말고 Valid 할게 있나?
}

bool Request::isOverTime()
{
	timeval now;

	gettimeofday(&now, NULL);

	long now_nbr = now.tv_sec * 1000 + now.tv_usec;
	long start_nbr = m_start_at.tv_sec * 1000 + m_start_at.tv_usec;
	
	return (now_nbr - start_nbr / 1000 >= TIMEOVER);
}

const Connection& Request::get_m_connection() const // 왜 얘는 포인터가 아니라 참조자일까요?
{
	return (*this->m_connection);
}

Server* Request::get_m_server() const
{
	return (this->m_server);
}

const Location& Request::get_m_location() const
{
	return (*this->m_location);
}

const Request::Method& Request::get_m_method() const
{
	return (this->m_method);
}

const std::string& Request::get_m_uri() const
{
	return (this->m_uri);
}

const Request::URIType& Request::get_m_uri_type() const
{
	return (this->m_uri_type);
}

const std::string &Request::get_m_protocol() const
{
	return (this->m_protocol);
}

const std::map<std::string, std::string>& Request::get_m_headers() const
{
	return (this->m_headers);
}

const Request::TransferType& Request::get_m_transfer_type() const
{
	return (this->m_transfer_type);
}

const std::string& Request::get_m_content() const
{
	return (this->m_content);
}

const std::string& Request::get_m_origin() const
{
	return (this->m_origin);	
}

Request::Request(Connection* connection, Server* server, std::string start_line): m_connection(connection), m_server(server), m_transfer_type(GENERAL)
{
	if (gettimeofday(&m_start_at, NULL) == -1)
		throw "gettimeofday error";
	std::vector<std::string> parsed = ft::split(start_line, ' ');
	std::vector<std::string>::iterator it = parsed.begin();

	if (parsed.size() != 3)
		throw "400 Bad Request";
	if (*it == "GET")
		m_method = GET;
	else if (*it == "HEAD")
		m_method = HEAD;
	else if (*it == "POST")
		m_method = POST;
	else if (*it == "PUT")
		m_method = PUT;
	else if (*it == "DELETE")
		m_method = DELETE;
	else if (*it == "OPTIONS")
		m_method = OPTIONS;
	else if (*it == "TRACE")
		m_method = TRACE;
	else
		throw "400 Bad Request";
	
	++it;
	if ((*it).length() > REQUEST_URI_LIMIT_SIZE)
		throw "414 URI Too Long";
	m_uri = *it;
	std::string path(TMP_ROOT + m_uri); // std::string path(m_location->m_root + m_uri)

	struct stat buf;
	stat(path.c_str(), &buf);
	if (S_ISREG(buf.st_mode))
	{
		if (path.find(TMP_CGI, path.length() - std::string(TMP_CGI).length()) != std::string::npos)
			m_uri_type = CGI_PROGRAM;
		else
			m_uri_type = FILE;
	}
	else if (S_ISDIR(buf.st_mode))
		m_uri_type = DIRECTORY;
	else
		throw "404 Not Found";
	
	++it;
	m_protocol = *it;
	if (m_protocol != "HTTP/1.1")
		throw "505 HTTP Version Not Supported";
}
