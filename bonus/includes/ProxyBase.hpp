#ifndef PROXYBASE_HPP
# define PROXYBASE_HPP

# include "webserv.hpp"
# include "Connection.hpp"

// class Request;
class ServerManager;

class ProxyBase
{
	public:
		enum ProxyType { UNDEFINED_PROXY, CACHE_PROXY, LOADBALANCE_PROXY, FILTER_PROXY };
	protected:
		ServerManager* m_manager;
		ProxyType m_type;
		std::string m_host;
		int m_port;
		int m_fd;
		int m_max_fd;
		fd_set m_read_set;
		fd_set m_read_copy_set;
		fd_set m_write_set;
		fd_set m_write_copy_set;
		std::multimap<std::string, int> m_servers;
		std::map<int, Connection> m_connections;
	private:
		/* send operation */
		bool hasSendWorkToClient(Connection& connection);
		bool runSendToClient(Connection& connection);
		bool hasSendWorkToServer(Connection& connection);
		bool runSendToServer(Connection& connection);

		/* read operation */
		bool hasRecvWorkFromServer(Connection& connection);
		bool runRecvFromServer(Connection& connection );
		bool hasRecvWorkFromClient(Connection& connection);
		bool runRecvFromClient(Connection& connection);

		/* connection management */
		bool hasNewConnection();
		int getUnusedConnectionFd();
		void closeConnection(int client_fd);
		bool acceptNewConnection();
		void closeOldConnection();

		/* proxy action */
		virtual void runProxyAction() = 0;
		void run();
	public:
		ProxyBase();
		ProxyBase(ServerManager* server_manager, const std::string& proxy_block);
		ProxyBase(const ProxyBase& copy);
		ProxyBase& operator=(const ProxyBase& obj);
		virtual ~ProxyBase();

		/* getter function */
		ServerManager* get_m_manager() const;
		ProxyType get_m_type() const;
		std::string get_type_to_string() const;
		const std::string& get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		int get_m_max_fd() const;
		fd_set get_m_read_set() const;
		fd_set get_m_read_copy_set() const;
		fd_set get_m_write_set() const;
		fd_set get_m_write_copy_set() const;
		const std::multimap<std::string, int>& get_m_servers() const;
		const std::map<int, Connection>& get_m_connections() const;

		/* setter function */
		void set_m_max_fd(int new_max_fd);

		/* declare member function */
		void runProxy();

		/* log function */
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
		void writeProxyHealthLog();
		void writeCloseConnectionLog(int client_fd);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
