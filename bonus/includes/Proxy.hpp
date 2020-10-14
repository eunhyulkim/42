#ifndef PROXY_HPP
# define PROXY_HPP

# include "webserv.hpp"
# include "Connection.hpp"

class ServerManager;

class Proxy
{
	public:
		enum ProxyType { UNDEFINED_PROXY, CACHE_PROXY, LOADBALANCE_PROXY, FILTER_PROXY };
		enum ServerConnectionStatus { WAIT, RUN };
		struct ServerConnection
		{
			int socket_fd;
			std::string key;
			std::string host;
			int port;
			ServerConnectionStatus status;
		};
	protected:
		ServerManager* m_manager;
		// ProxyType m_type;
		std::multimap<std::string, std::string> m_filter;
		std::map<std::string, std::string> m_cache;
		std::string m_host;
		int m_port;
		int m_fd;
		int m_max_fd;
		fd_set m_read_set;
		fd_set m_read_copy_set;
		fd_set m_write_set;
		fd_set m_write_copy_set;
		std::map<int, ServerConnection> m_server_connections;
		std::map<int, Connection> m_client_connections;
	private:
		/* util function */
		void resetConnectionServer(Connection& client_connection);
		void resetConnectionsFd(int from_fd, int to_fd);


		/* send operation */
		bool hasSendWorkToClient(Connection& client_connection);
		bool runSendToClient(Connection& client_connection);
		bool hasSendWorkToServer(Connection& client_connection);
		bool runSendToServer(Connection& client_connection);

		/* read operation */
		bool hasRecvWorkFromServer(Connection& client_connection);
		bool runRecvFromServer(Connection& client_connection );
		bool hasRecvWorkFromClient(Connection& client_connection);
		bool runRecvFromClient(Connection& client_connection);

		/* connection management */
		int connectServer(std::string host, int port);
		bool hasNewConnection();
		int getUnusedConnectionFd();
		void closeClientConnection(int client_fd);
		bool acceptNewConnection();
		void closeOldConnection();
		void resetMaxFd();

		/* proxy action */
		void runProxyAction(Connection& client_connection);
		void runFiltering(Connection& client_connection);
		void runCaching(Connection& client_connection);
		void runLoadBalancing(Connection& client_connection);
		void run();
	public:
		Proxy();
		Proxy(ServerManager* server_manager, const std::string& proxy_block);
		Proxy(const Proxy& copy);
		Proxy& operator=(const Proxy& obj);
		virtual ~Proxy();

		/* getter function */
		ServerManager* get_m_manager() const;
		// ProxyType get_m_type() const;
		// std::string get_type_to_string() const;
		const std::multimap<std::string, std::string>& get_m_filter() const;
		const std::string& get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		int get_m_max_fd() const;
		fd_set get_m_read_set() const;
		fd_set get_m_read_copy_set() const;
		fd_set get_m_write_set() const;
		fd_set get_m_write_copy_set() const;
		const std::map<int, ServerConnection>& get_m_server_connections() const;
		const std::map<int, Connection>& get_m_client_connections() const;

		/* setter function */
		void set_m_max_fd(int new_max_fd);
		void add_m_cache(Connection &connection);

		/* declare member function */
		void runProxy();

		/* log function */
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
		void writeProxyHealthLog();
		void writeCloseConnectionLog(int client_fd);
		void writeConnectServerLog(std::string host, int port);
		void reportConnectServerLog(std::string host, int port);
		void writeSendRequestLog(const Connection& connection);
		void writeSendResponseLog(const Connection& connection);



};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
