#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "Connection.hpp"
# include "Location.hpp"
# include "Request.hpp"
# include "Response.hpp"

// class Request;
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
		/* util */
		void basic_decode(std::string data, std::string& key, std::string& value);

		/* send operation */
		bool hasSendWork(Connection& connection);
		bool runSend(Connection& connection);
		bool hasExecuteWork(Connection& connection);
		bool runExecute(Connection& connection);

		/* connection management */
		// bool hasException(int client_fd);
		int getUnuseConnectionFd();
		bool hasNewConnection();
		bool acceptNewConnection();

		/* read operation */
		bool hasRequest(Connection& connection);

		void revertStdInOut();
		void createCGIResponse(int& status, headers_t& headers, std::string& body);
		bool parseStartLine(Connection& connection, Request& request);
		bool parseHeader(Connection& connection, Request& request);

		bool parseBody(Connection& connection, Request& request);


		int getHeaderLine(int client_fd, std::string& line);
		void headerParsing(Request &request, std::string& origin_message, int client_fd);
		std::string readBodyMessage(Request &request, std::string& origin_message, int client_fd);
		void recvRequest(Connection& connection, const Request& request);
		bool runRecvAndSolve(Connection& connection);

		/* cgi */
		char** createCGIEnv(const Request& request);

		/* create response */
		std::string getExtension(std::string path);
		std::string getMimeTypeHeader(std::string path);
		time_t getLastModified(std::string path);
		std::string getLastModifiedHeader(std::string path);

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

		/* declare member function */
		void run();

		void closeConnection(int client_fd);

		void solveRequest(Connection& connection, const Request& request);
		void executeAutoindex(Connection& connection, const Request& request);
		void executeGet(Connection& connection, const Request& request);
		void executeHead(Connection& connection, const Request& request);
		void executePost(Connection& connection, const Request& request);
		void executePut(Connection& connection, const Request& request);
		void executeDelete(Connection& connection, const Request& request);
		void executeOptions(Connection& connection, const Request& request);
		void executeTrace(Connection& connection, const Request& request);
		void executeCGI(Connection& connection, const Request& request);

		void createResponse(Connection& connection, int status, headers_t headers = headers_t(), std::string body = "");

		/* log function */
		void writeDetectNewConnectionLog();
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
		void writeDetectNewRequestLog(const Connection& connection);
		void writeCreateNewRequestLog(const Request& request);
		void reportCreateNewRequestLog(const Connection& connection, int status);
		void writeCreateNewResponseLog(const Response& response);
		void writeSendResponseLog(const Response& response);
		void writeCloseConnectionLog(int client_fd);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
