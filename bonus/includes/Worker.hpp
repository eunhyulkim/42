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
			fd_set read_set;
			fd_set read_copy_set;
			fd_set write_set;
			fd_set write_copy_set;
		};
		struct threadParam {
			ServerManager *manager;
			Server *server;
			Worker *worker;
			pthread_mutex_t *job_mutex;
			std::map<std::string, pthread_mutex_t> *uri_mutex;
			Job job;
		};
	private:
		pthread_t m_phtread;
		bool m_work_status;
		Fdset m_fdset;

		threadParam m_param;
		ServerManager *m_manager;
		Server *m_server;
		Worker *m_worker;
		Connection m_connection;
		pthread_mutex_t *m_job_mutex;
		std::map<std::string, pthread_mutex_t> *m_uri_mutex;
		int m_client_fd;
		Worker();
	public:
		Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* mutex, std::map<std::string, pthread_mutex_t> *uri_mutex);
		Worker(const Worker& copy);
		Worker& operator=(const Worker& obj);
		virtual ~Worker();

		/* fd util*/
		enum SetType {
			WRITE_SET, WRITE_COPY_SET, READ_SET, READ_COPY_SET, ALL_SET
		};
		void fdSet(int fd, SetType fdset);
		void fdZero(SetType fdset);
		void fdClear(int fd, SetType fdset);
		bool fdIsset(int fd, SetType fdset);
		void fdCopy(SetType fdset);
		int workerSelect();
		void resetMaxFd(int new_max_fd = -1);

		/* getter */
		int get_max_fd();
		const Connection& get_m_connection() const;

		/* setter */
		void set_m_work_status(bool status);
		void set_m_client_fd(int fd);

		/* declare member function */
		bool isFree() const;
		void run();
		void exit();
		bool runServer();
		void createConnection();
		void clearConnection();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Worker& worker);

#endif
