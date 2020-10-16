#ifndef PROXY_HPP
# define PROXY_HPP

# include "webserv.hpp"
# include "Connection.hpp"

class ProxyManager;

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
		struct Query { std::string condition; std::string key; std::string value; };
		struct LogQuery { std::vector<Query> querys; };
	protected:
		ProxyManager* m_manager;
		std::multimap<std::string, std::string> m_filters;
		std::vector<LogQuery> m_log_querys;
		std::map<std::string, std::string> m_caches;
		bool m_plugin_filter;
		bool m_plugin_log_if;
		bool m_plugin_cache;
		std::string m_host;
		int m_port;
		int m_fd;
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
		bool runCaching(Connection& client_connection);
		bool isSatisfiedQuery(Connection& client_connection, const Query& query);
		void writeLogIfCase(Connection& client_connection);
		void runLogIf(Connection& client_connection);
		void runLoadBalancing(Connection& client_connection);
	public:
		Proxy();
		Proxy(ProxyManager* proxy_manager, const std::string& proxy_block);
		Proxy(const Proxy& copy);
		Proxy& operator=(const Proxy& obj);
		virtual ~Proxy();

		/* getter function */
		ProxyManager* get_m_manager() const;
		const std::multimap<std::string, std::string>& get_m_filters() const;
		const std::vector<LogQuery>& get_m_log_querys() const;
		const std::map<std::string, std::string>& get_m_caches() const;
		bool is_on_plugin_filter() const;
		bool is_on_plugin_log_if() const;
		bool is_on_plugin_cache() const;
		const std::string& get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		const std::map<int, ServerConnection>& get_m_server_connections() const;
		const std::map<int, Connection>& get_m_client_connections() const;

		/* setter function */
		void set_m_max_fd(int new_max_fd);
		void add_m_cache(Connection &connection);

		/* main function */
		void run();

		/* log function */
		void writeCreateNewProxyLog(std::string host, int port);
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
		void writeProxyHealthLog();
		void writeCloseConnectionLog(int client_fd);
		void writeRecvRequestLog(const Connection& connection);
		void writeSendRequestLog(const Connection& connection);
		void writeRecvResponseLog(const Connection& connection);
		void writeSendResponseLog(const Connection& connection);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
