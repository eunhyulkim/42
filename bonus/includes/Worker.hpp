#ifndef WORKER_HPP
# define WORKER_HPP

# include <string>
# include <iostream>
# include <Python/Python.h>
# include "webserv.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Connection.hpp"

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
			Connection m_connection;
			pthread_mutex_t *job_mutex;
			pthread_mutex_t *live_mutex;
			std::map<std::string, pthread_mutex_t> *uri_mutex;
			Job job;
		};
	private:
		static std::map<std::string, std::string> mime_types;
		threadParam m_param;
		ServerManager *m_manager;
		Config *m_config;
		Server *m_server;
		Worker *m_worker;
		Connection m_connection;
		pthread_mutex_t *m_job_mutex;
		pthread_mutex_t *m_live_mutex;
		std::map<std::string, pthread_mutex_t> *m_uri_mutex;

		pthread_t m_pthread;
		bool m_work_status;
		Fdset m_fdset;
		int m_child_pid;
		int m_client_fd;
		Worker();
	public:
		Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* job_mutex, pthread_mutex_t* live_mutex,std::map<std::string, pthread_mutex_t> *uri_mutex);
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

		/* getter */
		int get_max_fd();
		const Connection& get_m_connection() const;

		/* setter */
		void set_m_work_status(bool status);
		void set_m_client_fd(int fd);

		std::string getExtension(std::string path);
		std::string getMimeTypeHeader(std::string path);
		time_t getLastModified(std::string path);
		std::string getLastModifiedHeader(std::string path);

		/* declare member function */
		void run();
		void createConnection(Job job);
		bool runWork();
		bool hasRequest();
		bool parseStartLine();
		bool parseHeader();
		bool parseBody();
		void recvRequest();
		void executeAutoindex();
		void executeGet();
		void executeHead();
		void executeTrace();
		void executePost();
		void executeOptions();
		void executePut();
		void executeDelete();
		char** createCGIEnv(const Request& request);
		void executeCGI();
		void solveRequest();
		bool runRecvAndSolve();
		bool hasSendWork();
		bool hasExecuteWork();
		bool runSend(bool& connect);
		bool runExecute(bool& connect);
		void createResponse(Connection& connection, int status, headers_t headers = headers_t(), std::string body = "");
		void createCGIResponse(int& status, headers_t& headers, std::string& body);




		void clearConnection();

		bool isFree() const;
		void exit();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Worker& worker);

#endif
