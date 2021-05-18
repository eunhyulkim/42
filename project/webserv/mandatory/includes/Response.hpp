/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:40:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/17 04:40:31 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Response_HPP
# define Response_HPP

# include "webserv.hpp"

class Connection;

class Response
{
	public:
		enum ConnectionType { CLOSE, KEEP_ALIVE, };
		enum TransferType { GENERAL, CHUNKED };
		enum Phase { READY, ON_HEADER, ON_BODY, COMPLETE };
		static std::map<int, std::string> status;
	private:
		Connection* m_connection;
		ConnectionType m_connection_type;
		int m_status_code;
		std::string m_status_description;
		std::map<std::string, std::string> m_headers;
		TransferType m_transfer_type;
		std::string m_content;
		Phase m_phase;
	public:
		Response();
		Response(Connection* connection, int status_code, std::string body = "");
		Response(const Response& copy);
		Response& operator=(const Response& obj);
		virtual ~Response();

		/* getter function */
		Connection *get_m_connection() const;
		ConnectionType get_m_connection_type() const;
		int get_m_status_code() const;
		std::string get_m_status_description() const;
		const std::map<std::string, std::string>& get_m_headers() const;
		TransferType get_m_transfer_type() const;
		std::string get_m_content() const;
		Phase get_m_phase() const;

		/* setter */
		void addHeader(std::string header_key, std::string header_value);
		void addContent(const std::string& body);
		void set_m_status_code(int status_code);
		void set_m_transfer_type(TransferType transfer_type);
		void set_m_phase(Phase phase);
		void clear();

		/* member function */	
		std::string getString() const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Response& Response);

std::map<int, std::string> make_status ();

#endif
