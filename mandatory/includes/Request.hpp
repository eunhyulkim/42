/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopar <yopar@student.42seoulseoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:42:22 by yopark            #+#    #+#             */
/*   Updated: 2020/10/02 21:36:435 by yopar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "webserv.hpp"
# include "Location.hpp"

class Connection;
class Server;

class Request
{
public:
	enum Method { DEFAULT, GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
	enum URIType { DIRECTORY, FILE, FILE_TO_CREATE, CGI_PROGRAM };
	enum TransferType { GENERAL, CHUNKED };
	enum Phase { READY, ON_HEADER, ON_BODY, COMPLETE };
private:
	Connection* m_connection;
	Server *m_server;
	Location *m_location;
	timeval m_start_at;
	Phase m_phase;

	Method m_method;
	std::string m_uri;
	URIType m_uri_type;
	std::string m_protocol;
	std::map<std::string, std::string> m_headers;
	int m_speical_header_count;
	TransferType m_transfer_type;
	std::string m_content;
	std::string m_query;
	std::string m_script_translated;
	std::string m_path_translated;
	std::string m_path_info;
	std::string m_origin;

	bool parseMethod(std::string method_string);
	bool assignLocationMatchingUri(std::string uri);
	std::string parseUri();
public:
	Request();
	Request(Connection* conneciton, Server *server, std::string start_line);
	Request(const Request &x);
	Request &operator=(const Request &x);
	virtual ~Request();

	/* getter */
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
	const std::string &get_m_query() const;
	const std::string &get_m_path_info() const;
	const std::string &get_m_origin() const;
	const std::string &get_m_path_translated() const;
	const std::string &get_m_script_translated() const;
	Phase get_m_phase() const;
	int get_m_special_header_count() const;

	/* setter */
	void addContent(std::string added_content);
	void addOrigin(std::string added_origin, bool limit_ignore = false);
	void addHeader(std::string header);
	void set_m_method(Method method);
	void set_m_phase(Phase phase);
	void set_m_transfer_type(TransferType transfer_type);
	void addSpecialHeaderCount();
	void clear();

	/* member function */
	bool isValidHeader(std::string header);
	bool isOverTime() const;
};

/* global operator overload */
std::ostream &operator<<(std::ostream &out, const Request &request);

#endif
