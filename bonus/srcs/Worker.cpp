#include "../includes/Worker.hpp"

extern std::queue<int> g_job_queue;
extern bool g_worker_live;


/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Worker::Worker() {}
Worker::Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* mutex)
{
	m_work_status = false;
	m_param.manager = server_manager;
	m_param.server = server;
	m_param.worker = this;
	m_param.mutex = mutex;
}

Worker::Worker(const Worker& copy)
{
	/* copy-constructor code */
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Worker::~Worker()
{
	/* destructor code */
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Worker& Worker::operator=(const Worker& obj)
{
	if (this == &obj)
		return (*this);
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Worker& worker)
{
	/* ostream output overload code */
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* getter code */

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Worker::set_m_work_status(bool status) { m_work_status = status };

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void workWithConnection(void *parameter)
{
	Worker::threadParam *param = reinterpret_cast<Worker::threadParam *>(parameter);
	ServerManager* manager = param->manager;
	Server* server = param->server;
	Worker* worker = param->worker;
	int client_fd = param->client_fd;
	Worker::Fdset fdset;

	ft::fdZero(&fdset.m_read_set);
	ft::fdZero(&fdset.m_read_copy_set);
	ft::fdZero(&fdset.m_write_set);
	ft::fdZero(&fdset.m_write_copy_set);

	// SELECT AND PROCESS WITH OLD SERVER FUNCTION; WHEN END, CLOSE CONNECTION FD;
}

void *worker_routine(void *parameter)
{
	Worker::threadParam *param = reinterpret_cast<Worker::threadParam *>(parameter);
	Worker* worker = param->worker;
	pthread_mutex_t* mutex = param->mutex;
	int client_fd = -1;
	int pid;
	int stat;

	while (g_worker_live)
	{
		pthread_mutex_lock(mutex);
		if (g_job_queue.empty()) {
			pthread_mutex_unlock(mutex);
			continue ;
		}
		worker->set_m_work_status(true);
		param->client_fd = g_job_queue.front();
		g_job_queue.pop();
		pthread_mutex_unlock(mutex);
		pid = fork();
		if (pid == 0) {
			workWithConnection(param);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0) {
			close(client_fd);
			worker->set_m_work_status(false);
		}
		else {
			waitpid(pid, &stat, 0);
			worker->set_m_work_status(false);
		}
	}

	if (client_fd != -1)
		close(client_fd);
	exit(EXIT_SUCCESS);
}

bool Worker::isFree() {
	return (m_work_status == false);
}

void Worker::run() {
	pthread_create(&m_phtread, NULL, worker_routine, reinterpret_cast<void *>(&m_param));
}

void Worker::exit() {
	pthread_join(m_phtread, NULL);
}

