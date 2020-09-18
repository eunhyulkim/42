/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:48:48 by yopark            #+#    #+#             */
/*   Updated: 2020/09/18 16:29:54 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

class Connection;
class Server;
class Location;

class Request {
    private:
        enum Method { GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
        enum URIType { DIRECTORY, FILE, CGI_PROGRAM };
        enum TransferType { GENERAL, CHUNKED };

        Connection* m_connection;
        Server* m_server;
        Location* m_location;
        timeval m_start_at;

        Method m_method;
        std::string m_uri;
        URIType m_uri_type;
		std::string m_protocol;
        std::map<std::string, std::string> m_headers;
        TransferType m_transfer_type;
        std::string m_content;
        std::string m_origin;
    public:
        void add_content(std::string added_content);
        void add_origin(std::string added_origin);
        void add_header(std::string header);
        bool isValidHeader(std::string header);
        bool isOverTime();
        
        const Connection& get_m_connection() const;
        Server* get_m_server() const;
        const Location& get_m_location() const;
        const Method& get_m_method() const;
        const std::string& get_m_uri() const;
        const URIType& get_m_uri_type() const;
		const std::string &get_m_protocol() const;
        const std::map<std::string, std::string>& get_m_headers() const;
        const TransferType& get_m_transfer_type() const;
        const std::string& get_m_content() const;
        const std::string& get_m_origin() const;

        Request(Connection* connection, Server* server, std::string start_line);
};
