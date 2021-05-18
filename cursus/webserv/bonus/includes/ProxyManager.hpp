#ifndef PROXY_MANAGER_HPP
# define PROXY_MANAGER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "Proxy.hpp"

class ProxyManager
{
	public:
		static int log_fd;
	private:
		std::vector<Proxy> m_proxys;
		std::set<int> m_proxy_fdset;
        Config m_config;
        int m_max_fd;
        fd_set m_read_set;
        fd_set m_read_copy_set;
		fd_set m_write_set;
		fd_set m_write_copy_set;

		/* functions for parse configuration files */
		bool splitConfigString(std::string config_string, std::string& config_block, std::vector<std::string>& proxy_blocks);
        bool isValidConfigBlock(std::string& config_block);
        bool isValidProxyBlock(std::string& proxy_block, Config& config);
	public:
		ProxyManager();
		ProxyManager(const ProxyManager&);
		ProxyManager& operator=(const ProxyManager& obj);
		virtual ~ProxyManager();

		/* getter & setter */
		Config* configClone();
		const std::vector<Proxy>& get_m_proxys() const;
		const std::set<int>& get_m_proxy_fdset() const;
		Config get_m_config() const;
		int get_m_max_fd() const;
		void set_m_max_fd(int max_fd);
		void set_m_config(const Config& config);
		
		/* FD functions */
		enum SetType {
			WRITE_SET, WRITE_COPY_SET, READ_SET, READ_COPY_SET, ERROR_SET, ERROR_COPY_SET, ALL_SET
		};
		void fdSet(int fd, SetType fdset);
		void fdZero(SetType fdset);
		void fdClear(int fd, SetType fdset);
		bool fdIsset(int fd, SetType fdset);
		void fdCopy(SetType fdset);
		void resetMaxFd(int new_max_fd = -1);

		/* member function */
		void createServer(const std::string& configuration_file_path, char **env);
		void runServer();
		void exitServer(const std::string& error_msg);

		/* log function */
		void openLog();
		void writeCreateServerLog();
		void writeServerHealthLog(bool ignore_interval = false);
};

std::ostream&
operator<<(std::ostream& out, const ProxyManager&);

#endif
