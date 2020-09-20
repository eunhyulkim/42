#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <queue>
# include "Location.hpp"
# include "Connection.hpp"
# include "Request.hpp"
# include "ServerManager.hpp"

# define SEND_RESPONSE_AT_ONCE 5

class Server
{
	private:
		ServerManager* m_manager;
		std::string m_server_name;
		std::string m_host;
		int m_port;
		int m_fd;
		int m_request_uri_limit_size;
		int m_request_header_limit_size;
		int m_limit_client_body_size;
		std::string m_default_error_page;
		std::vector<Location> m_locations;
		std::map<int, Connection> m_connections;
		std::queue<Response> m_responses;
	public:
		Server();
		Server(const std::string& server_block, const std::string& location_blocks);
		Server(const Server& copy);
		Server& operator=(const Server& obj);
		virtual ~Server();

		/* getter function */
		std::string get_m_server_name() const;
		std::string get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		int get_m_request_uri_limit_size() const;
		int get_m_request_header_limit_size() const;
		int get_m_limit_client_body_size() const;
		std::string get_m_default_error_page() const;

		/* setter function */
		void set_m_server_name(std::string server_name);
		void set_m_host(std::string host);
		void set_m_port(int port);
		void set_m_fd(int fd);
		void set_m_request_uri_limit_size(int request_uri_limit_size);
		void set_m_request_header_limit_size(int request_header_limit_size);
		void set_m_limit_client_body_size(int limit_client_body_size);
		void set_m_default_error_page(std::string default_error_page);

		/* declare member function */
		void run();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
