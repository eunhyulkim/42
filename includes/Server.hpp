#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <map>
# include <vector>
# include <queue>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "libft.hpp"
# include "Location.hpp"
# include "ServerManager.hpp"
# include "Connection.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "Base64.hpp"

# define SEND_RESPONSE_AT_ONCE 5
# define RESPONSE_OVERLOAD_COUNT 20

# include <vector>
# include <set>
# include <map>
# include "Location.hpp"
# include "Request.hpp"
# include "libft.hpp"

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
		Config* m_config;
		std::vector<Location> m_locations;
		std::map<int, Connection> m_connections;
		std::queue<Response> m_responses;
	private:
		void basic_decode(std::string data, std::string& key, std::string& value);
		std::string inet_ntoa(unsigned int address);
	public:
		Server();
		Server(ServerManager* server_manager, const std::string& server_block, std::vector<std::string>& location_blocks, Config* config);
		Server(const Server& copy);
		Server& operator=(const Server& obj);
		virtual ~Server();

		/* getter function */
		const std::string& get_m_server_name() const;
		const std::string& get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		int get_m_request_uri_limit_size() const;
		int get_m_request_header_limit_size() const;
		int get_m_limit_client_body_size() const;
		const std::string& get_m_default_error_page() const;
		Config* get_m_config() const;
		const std::vector<Location>& get_m_locations() const;
		const std::map<int, Connection>& get_m_connections() const;
		const std::queue<Response>& get_m_responses() const;

		/* setter function */
		// void set_m_server_name(std::string server_name);
		// void set_m_host(std::string host);
		// void set_m_port(int port);
		// void set_m_fd(int fd);
		// void set_m_request_uri_limit_size(int request_uri_limit_size);
		// void set_m_request_header_limit_size(int request_header_limit_size);
		// void set_m_limit_client_body_size(int limit_client_body_size);
		// void set_m_default_error_page(std::string default_error_page);

		/* declare member function */
		bool hasException(int client_fd);
		void closeConnection(int client_fd);
		bool hasNewConnection();
		void acceptNewConnection();
		void run();

		// int isSendable(int client_fd);
		// int sendResponse(Response response);

		// bool hasRequest(int client_fd);
		// Request recvRequest(int client_fd);

		void solveRequest(const Request& request);		
		// void executeAutoindex(const Request& request);
		// int executeGet(Request request);
		// int executeHead(Request request);
		// int executePut(Request request);
		// int executePost(Request request);
		// int executeDelete(Request request);
		// int executeOptions(Request request);
		// int executeTrace(Request request);

		// char** createCGIEnv(Request request);
		// int executeCGI(Request request);
		
		// int createResponse(int status);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
