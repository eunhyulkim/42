#ifndef SERVER_MANAGER_HPP
# define SERVER_MANAGER_HPP

# include <string>
# include <iostream>
# include <vector>
# include <set>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <algorithm>
# include "Server.hpp"
# include "Config.hpp"

# define REQUEST_URI_LIMIT_SIZE_MIN 64
# define REQUEST_URI_LIMIT_SIZE_MAX 8192
# define REQUEST_HEADER_LIMIT_SIZE_MIN 64
# define REQUEST_HEADER_LIMIT_SIZE_MAX 8192
# define LIMIT_CLIENT_BODY_SIZE_MAX 8192

class ServerManager
{
	public:
		std::vector<Server> m_servers;
        Config m_config;
        int m_max_fd;
        fd_set m_read_set;
        fd_set m_read_copy_set;
        fd_set m_write_set;
        fd_set m_write_copy_set;
        fd_set m_error_set;
        fd_set m_error_copy_set;
		
		/* functions for parse configuration files */
		bool splitConfigString(std::string config_string, std::string& config_block, std::vector<std::string>& server_strings);
        bool splitServerString(std::string server_string, std::string& server_block, std::vector<std::string>& location_blocks);
        bool isValidConfigBlock(std::string& config_block);
        bool isValidServerBlock(std::string& server_block);
        bool isValidLocationBlock(std::string& location_block);
	public:
		ServerManager();
		ServerManager(const ServerManager& copy);
		ServerManager& operator=(const ServerManager& obj);
		virtual ~ServerManager();

		/* getter & setter function */
		Config get_m_config() const;
		int get_m_max_fd() const;
		void set_m_max_fd(int max_fd);
		void set_m_config(const Config& config);
		
		/* FD functions to access the ServerManager from Server */
		enum SetType {
			WRITE_SET, WRITE_COPY_SET, READ_SET, READ_COPY_SET, ERROR_SET, ERROR_COPY_SET,
		};
		void fdSet(int fd, SetType fdset);
		void fdZero(SetType fdset);
		void fdClear(int fd, SetType fdset);
		bool fdIsset(int fd, SetType fdset);
		void fdCopy(SetType fdset);

		/* declare member function */
		void printFdSets(); // function for develop
		void createServer(const std::string& configuration_file_path);
		void runServer();
		void exitServer(const std::string& error_msg);
};

#endif
