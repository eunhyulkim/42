/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:42:22 by yopark            #+#    #+#             */
/*   Updated: 2020/09/21 15:57:48 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <map>
# include <sys/time.h>
# include <sys/stat.h>
# include <cstring>

# include "libft.hpp"

# define REQUEST_TIMEOVER 10

class Connection;
class Server;
class Location;

class Request
{
public:
	enum Method { GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
	enum URIType { DIRECTORY, FILE, CGI_PROGRAM };
	enum TransferType { GENERAL, CHUNKED };
private:
	Connection *m_connection;
	Server *m_server;
	Location *m_location;
	timeval m_start_at;

	Method m_method;
	std::string m_uri;
	URIType m_uri_type;
	std::string m_protocol;
	std::map<std::string, std::string> m_headers;
	TransferType m_transfer_type;
	std::string m_content;
	std::string m_origin;

	std::string m_path_translated;

	Request();

public:
	Request(Connection *conneciton, Server *server, std::string start_line);
	Request(const Request &x);
	Request &operator=(const Request &x);	
	virtual ~Request();

	void add_content(std::string added_content);
	void add_origin(std::string added_origin);
	void add_header(std::string header);
	bool isValidHeader(std::string header);
	bool isOverTime();

	Connection *get_m_connection() const;
	Server *get_m_server() const;
	Location *get_m_location() const;
	Method get_m_method() const;
	std::string get_m_method_to_string() const;
	const std::string &get_m_uri() const;
	URIType get_m_uri_type() const;
	const std::string &get_m_protocol() const;
	const std::map<std::string, std::string> &get_m_headers() const;
	TransferType get_m_transfer_type() const;
	const std::string &get_m_content() const;
	const std::string &get_m_origin() const;
	const std::string &get_m_path_translated() const;
};

/* global operator overload */
std::ostream &operator<<(std::ostream &out, const Request &request);

#endif
