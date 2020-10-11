#include "Server.hpp"
#include "Worker.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Worker::Worker() {}
Worker::Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* job_mutex, std::map<std::string, pthread_mutex_t> *uri_mutex)
{
	m_manager = m_param.manager = server_manager;
	m_server = m_param.server = server;
	m_worker = m_param.worker = this;
	m_job_mutex = m_param.job_mutex = job_mutex;
	m_uri_mutex = m_param.uri_mutex = uri_mutex;
	m_work_status = false;
	ft::fdZero(&m_fdset.read_set);
	ft::fdZero(&m_fdset.read_copy_set);
	ft::fdZero(&m_fdset.write_set);
	ft::fdZero(&m_fdset.write_copy_set);
	m_client_fd = -1;
}

Worker::Worker(const Worker& copy)
{
	m_param.manager = copy.m_param.manager;
	m_server = m_param.server = copy.m_param.server;
	m_worker = m_param.worker = copy.m_param.worker;
	m_job_mutex = m_param.job_mutex = copy.m_param.job_mutex;
	m_uri_mutex = m_param.uri_mutex = copy.m_param.uri_mutex;
	m_work_status = copy.m_work_status;
	m_fdset.read_set = copy.m_fdset.read_set;
	m_fdset.read_copy_set = copy.m_fdset.read_copy_set;
	m_fdset.write_set = copy.m_fdset.write_set;
	m_fdset.write_copy_set = copy.m_fdset.write_copy_set;
	m_client_fd = copy.m_client_fd;
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
	m_param.manager = obj.m_param.manager;
	m_server = m_param.server = obj.m_param.server;
	m_worker = m_param.worker = obj.m_param.worker;
	m_job_mutex = m_param.job_mutex = obj.m_param.job_mutex;
	m_uri_mutex = m_param.uri_mutex = obj.m_param.uri_mutex;
	m_work_status = obj.m_work_status;
	m_fdset.read_set = obj.m_fdset.read_set;
	m_fdset.read_copy_set = obj.m_fdset.read_copy_set;
	m_fdset.write_set = obj.m_fdset.write_set;
	m_fdset.write_copy_set = obj.m_fdset.write_copy_set;
	m_client_fd = obj.m_client_fd;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Worker&)
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

void Worker::set_m_work_status(bool status) { m_work_status = status; }
void Worker::set_m_client_fd(int fd) { m_client_fd = fd; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool isOverTime()
{
	return (false);
}

void workWithConnection(Worker::threadParam *param)
{
	// ServerManager* manager = param->manager;
	Server* server = param->server;
	Worker* worker = param->worker;
	int client_fd = param->job.client_fd;

	worker->fdZero(Worker::ALL_SET);
	worker->fdSet(client_fd, Worker::READ_SET);

	// SELECT AND PROCESS WITH OLD SERVER FUNCTION; WHEN END, CLOSE CONNECTION FD;
	int cnt;

	while (server->get_m_server_live())
	{
		worker->fdCopy(Worker::ALL_SET);

		if ((cnt = worker->workerSelect()) == -1)
		{
			perror("why?");
			// ft::log(ServerManager::access_fd, ServerManager::error_fd, "[Failed][Function]Select function failed(return -1)");
			throw std::runtime_error("select error");
		}
		else if (cnt == 0)
		{
			if (isOverTime())
				break ;
			continue ;
		}
		// writeServerHealthLog();
		if (!worker->runServer())
			break ;
	}
	close(client_fd);
	worker->clearConnection();
	// exitServer("server exited.\n");
	return ;
}

void *worker_routine(void *parameter)
{
	Worker::threadParam *param = reinterpret_cast<Worker::threadParam *>(parameter);
	Worker* worker = param->worker;
	Server* server = param->server;
	pthread_mutex_t* job_mutex = param->job_mutex;
	std::queue<Job>& job_queue = const_cast<std::queue<Job>& >(server->get_m_job_queue());

	printf("job mutex: %p\n", job_mutex);
	while (server->get_m_server_live())
	{
		pthread_mutex_lock(job_mutex);
		if (server->get_m_job_queue().empty()) {
			pthread_mutex_unlock(job_mutex);
			continue ;
		}
		worker->set_m_work_status(true);
		param->job = job_queue.front();
		job_queue.pop();
		pthread_mutex_unlock(job_mutex);
		worker->set_m_client_fd(param->job.client_fd);
		worker->createConnection();
		workWithConnection(param);
	}
	exit(EXIT_SUCCESS);
}

bool Worker::runServer()
{
	return (m_server->work(m_client_fd, this));
}

bool Worker::isFree() const {
	return (m_work_status == false);
}

void Worker::run() {
	pthread_create(&m_phtread, NULL, worker_routine, reinterpret_cast<void *>(&m_param));
}

void Worker::exit() {
	pthread_join(m_phtread, NULL);
}

void Worker::createConnection() {
	m_connection = Connection(m_param.job.client_fd, m_param.job.ip, m_param.job.port);
}

void Worker::clearConnection() {
	m_connection.clear();
}

void
Worker::fdSet(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdSet(fd, &this->m_fdset.write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdSet(fd, &this->m_fdset.write_copy_set);
	else if (fdset == READ_SET)
		ft::fdSet(fd, &this->m_fdset.read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdSet(fd, &this->m_fdset.read_copy_set);
}

void
Worker::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.write_set);
	else if (fdset == WRITE_COPY_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.write_copy_set);
	else if (fdset == READ_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.read_set);
	else if (fdset == READ_COPY_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.read_copy_set);
}

void
Worker::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.write_set);
	else if (fdset == WRITE_COPY_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.write_copy_set);
	else if (fdset == READ_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.read_set);
	else if (fdset == READ_COPY_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.read_copy_set);
}

bool
Worker::fdIsset(int fd, SetType fdset)
{
	bool ret = false;

	if (fdset == WRITE_SET || fdset == ALL_SET)
		ret = ft::fdIsset(fd, &this->m_fdset.write_set);
	else if (fdset == WRITE_COPY_SET || fdset == ALL_SET)
		ret = ft::fdIsset(fd, &this->m_fdset.write_copy_set);
	else if (fdset == READ_SET || fdset == ALL_SET)
		ret = ft::fdIsset(fd, &this->m_fdset.read_set);
	else if (fdset == READ_COPY_SET || fdset == ALL_SET)
		ret = ft::fdIsset(fd, &this->m_fdset.read_copy_set);
	return (ret);
}

void
Worker::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_fdset.write_copy_set);
		this->m_fdset.write_copy_set = this->m_fdset.write_set;
	}
	if (fdset == READ_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_fdset.read_copy_set);
		this->m_fdset.read_copy_set = this->m_fdset.read_set;
	}
}

int
Worker::get_max_fd()
{
	for (int i = 1024; i >= 0; --i)
	{
		if (ft::fdIsset(i, &m_fdset.read_set) || ft::fdIsset(i, &m_fdset.write_set))
			return (i);
	}
	return (-1);
}

const Connection& Worker::get_m_connection() const { return (m_connection); }

int
Worker::workerSelect()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	return (select(get_max_fd() + 1, &m_fdset.read_copy_set, &m_fdset.write_copy_set, NULL, &timeout));
}