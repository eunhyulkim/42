#ifndef SERVER_MANAGER_HPP
# define SERVER_MANAGER_HPP

# include <string>
# include <iostream>
# include <vector>
# include <sys/select.h>
# include <sys/types.h>
# include <unistd.h>
# include "Config.hpp"

/* 테스트를 위한 임시 클래스 */
class Server {};

class ServerManager
{
	private:
		std::vector<Server> m_servers;
        Config m_config;
        int m_max_fd;
        fd_set m_read_set;
        fd_set m_read_copy_set;
        fd_set m_write_set;
        fd_set m_write_copy_set;
        fd_set m_error_set;
        fd_set m_error_copy_set;

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
		void printFdSets();
};

#endif
