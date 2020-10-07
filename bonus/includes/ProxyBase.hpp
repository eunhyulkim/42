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

class ProxyBase
{
	protected:
		ServerManager* m_manager;
		std::string m_server_name;
		std::string m_host;
		int m_port;
		int m_fd;
		std::map<int, Connection> m_connections;
	private:
		/* util */
		std::string inet_ntoa(unsigned int address);

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
		bool parseStartLine(Connection& connection, Request& request);
		bool parseHeader(Connection& connection, Request& request);

		bool parseBody(Connection& connection, Request& request);

		int getHeaderLine(int client_fd, std::string& line);
		void headerParsing(Request &request, std::string& origin_message, int client_fd);
		std::string readBodyMessage(Request &request, std::string& origin_message, int client_fd);
		void recvRequest(Connection& connection, const Request& request);
		bool runRecvAndSolve(Connection& connection);

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
