#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "Connection.hpp"
# include "Location.hpp"
# include "Response.hpp"
# include "Request.hpp"

class Request;
class ServerManager;

class Server
{
	public:
	private:
		static std::map<std::string, std::string> mime_types;
		ServerManager* m_manager;
		std::string m_server_name;
		std::string m_host;
		int m_port;
		int m_fd;
		size_t m_request_uri_limit_size;
		size_t m_request_header_limit_size;
		size_t m_limit_client_body_size;
		std::string m_default_error_page;
		Config* m_config;
		std::vector<Location> m_locations;
		std::map<int, Connection> m_connections;
		std::queue<Response> m_responses;
	private:
		void basic_decode(std::string data, std::string& key, std::string& value);
		std::string inet_ntoa(unsigned int address);
		std::string getExtension(std::string path);
		std::string getMimeTypeHeader(std::string path);
		time_t getLastModified(std::string path);
		std::string getLastModifiedHeader(std::string path);
		char** createCGIEnv(const Request& request);
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
		size_t get_m_request_uri_limit_size() const;
		size_t get_m_request_header_limit_size() const;
		size_t get_m_limit_client_body_size() const;
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
		bool acceptNewConnection();
		void run();

		bool isSendable(int client_fd);
		void sendResponse(Response response);

		bool hasRequest(int client_fd);
		Request recvRequest(int client_fd, Connection* connection);

		void solveRequest(const Request& request);
		void executeAutoindex(const Request& request);
		void executeGet(const Request& request);
		void executeHead(const Request& request);
		void executePost(const Request& request);
		void executePut(const Request& request);
		void executeDelete(const Request& request);
		void executeOptions(const Request& request);
		void executeTrace(const Request& request);
		void executeCGI(const Request& request);

		void createResponse(Connection* connection, int status, HEADERS headers = HEADERS(), std::string body = "");

		/* log function */
		void writeDetectNewConnectionLog();
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
		void writeDetectNewRequestLog(const Connection& connection);
		void writeCreateNewRequestLog(const Request& request);
		void reportCreateNewRequestLog(const Connection& connection, int status);
		void writeCreateNewResponseLog(const Response& response);
		void writeCloseConnectionLog(int client_fd);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
