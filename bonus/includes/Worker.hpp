#ifndef WORKER_HPP
# define WORKER_HPP

# include <string>
# include <iostream>
# include "webserv.hpp"

class ServerManager;
class Server;

class Worker
{
	public:
		struct Fdset {
			fd_set m_read_set;
			fd_set m_read_copy_set;
			fd_set m_write_set;
			fd_set m_write_copy_set;
		};
		struct threadParam {
			ServerManager *manager;
			Server *server;
			Worker *worker;
			pthread_mutex_t *mutex;
			int client_fd;
		};
	private:
		pthread_t m_phtread;
		bool m_work_status;
		threadParam m_param;
		Worker();
	public:
		Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* mutex);
		Worker(const Worker& copy);
		Worker& operator=(const Worker& obj);
		virtual ~Worker();

		/* getter */

		/* setter */
		void set_m_work_status(bool status);

		/* declare member function */
		bool isFree();
		void run();
		void exit();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Worker& worker);

#endif
