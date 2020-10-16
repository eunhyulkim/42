#include "Connection.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Connection::Connection() {}
Connection::Connection(int fd, const std::string& client_ip, int client_port)
: m_status(ON_WAIT),
m_client_fd(fd),
m_server_fd(-1),
m_read_from_server_fd(-1),
m_write_to_server_fd(-1),
m_request(),
m_token_size(-1),
m_readed_size(0),
m_response(),
m_rbuf_from_client(),
m_rbuf_from_server(),
m_wbuf(),
m_wbuf_data_size(0),
m_send_data_size(0),
m_last_request_at(),
m_client_ip(client_ip),
m_client_port(client_port),
m_is_cached(false),
m_is_filtered(false)
{
	this->m_last_request_at.tv_sec = 0;
	this->m_last_request_at.tv_usec = 0;
	set_m_last_request_at();
}

Connection::Connection(const Connection& copy)
: m_status(copy.get_m_status()),
m_client_fd(copy.get_m_client_fd()),
m_server_fd(copy.get_m_server_fd()),
m_read_from_server_fd(copy.get_m_read_from_server_fd()),
m_write_to_server_fd(copy.get_m_write_to_server_fd()),
m_request(copy.get_m_request()),
m_token_size(copy.get_m_token_size()),
m_readed_size(copy.get_m_readed_size()),
m_response(copy.get_m_response()),
m_rbuf_from_client(copy.get_m_rbuf_from_client()),
m_rbuf_from_server(copy.get_m_rbuf_from_server()),
m_wbuf(copy.get_m_wbuf()),
m_wbuf_data_size(copy.m_wbuf_data_size),
m_send_data_size(copy.m_send_data_size),
m_last_request_at(copy.get_m_last_request_at()),
m_client_ip(copy.get_m_client_ip()),
m_client_port(copy.get_m_client_port()),
m_is_cached(copy.m_is_cached),
m_is_filtered(copy.m_is_filtered) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Connection::~Connection()
{
	this->m_status = ON_WAIT;
	this->m_client_fd = 0;
	this->m_server_fd = -1;
	this->m_read_from_server_fd = -1;
	this->m_write_to_server_fd = -1;
	this->m_token_size = -1;
	this->m_readed_size = 0;
	this->m_rbuf_from_client.clear();
	this->m_rbuf_from_server.clear();
	this->m_wbuf.clear();
	m_wbuf_data_size = 0;
	m_send_data_size = 0;
	this->m_last_request_at.tv_sec = 0;
	this->m_last_request_at.tv_usec = 0;
	this->m_client_ip.clear();
	this->m_client_port = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Connection& Connection::operator=(const Connection& obj)
{
	if (this == &obj)
		return (*this);
	m_status = obj.get_m_status();
	m_client_fd = obj.get_m_client_fd();
	m_server_fd = obj.get_m_server_fd();
	m_read_from_server_fd = obj.get_m_read_from_server_fd();
	m_write_to_server_fd = obj.get_m_write_to_server_fd();
	m_request = obj.get_m_request();
	m_token_size = obj.get_m_token_size();
	m_readed_size = obj.get_m_readed_size();
	m_response = obj.get_m_response();
	m_rbuf_from_client = obj.get_m_rbuf_from_client();
	m_rbuf_from_server = obj.get_m_rbuf_from_server();
	m_wbuf = obj.get_m_wbuf();
	m_wbuf_data_size = obj.m_wbuf_data_size;
	m_send_data_size = obj.m_send_data_size;
	m_last_request_at = obj.get_m_last_request_at();
	m_client_ip = obj.get_m_client_ip();
	m_client_port = obj.get_m_client_port();
	m_is_cached = obj.m_is_cached;
	m_is_filtered = obj.m_is_filtered;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Connection& connection)
{
	out << "FD: " << connection.get_m_client_fd() << std::endl
	<< "LAST_REQUEST_SEC: " << connection.get_m_last_request_at().tv_sec << std::endl
	<< "LAST_REQUEST_USEC: " << connection.get_m_last_request_at().tv_usec << std::endl
	<< "CLIENT_IP: " << connection.get_m_client_ip() << std::endl
	<< "CLIENT_PORT: " << connection.get_m_client_port() << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

Connection::Status Connection::get_m_status() const { return (this->m_status); }
int Connection::get_m_client_fd() const { return (this->m_client_fd); }
int Connection::get_m_server_fd() const { return (this->m_server_fd); }
int Connection::get_m_read_from_server_fd() const { return (this->m_read_from_server_fd); }
int Connection::get_m_write_to_server_fd() const { return (this->m_write_to_server_fd); }
const Request& Connection::get_m_request() const { return (this->m_request); }
int Connection::get_m_token_size() const { return (this->m_token_size); }
int Connection::get_m_readed_size() const { return (this->m_readed_size); }
const std::string& Connection::get_m_rbuf_from_client() const { return (this->m_rbuf_from_client); }
const std::string& Connection::get_m_rbuf_from_server() const { return (this->m_rbuf_from_server); }
const std::string& Connection::get_m_wbuf() const { return (this->m_wbuf); }
const Response& Connection::get_m_response() const { return (this->m_response); }
timeval Connection::get_m_last_request_at() const { return (this->m_last_request_at); }
std::string Connection::get_m_client_ip() const { return (this->m_client_ip); }
int Connection::get_m_client_port() const { return (this->m_client_port); }
Worker* Connection::get_m_worker() const { return (this->m_worker); }
bool Connection::get_m_is_cached() const { return (m_is_cached); }
bool Connection::get_m_is_filtered() const { return (m_is_filtered); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Connection::set_m_client_fd(int fd) { m_client_fd = fd; }
void Connection::set_m_last_request_at()
{
	timeval now;
	if (gettimeofday(&now, reinterpret_cast<struct timezone *>(NULL)) == -1)
		return ;
	this->m_last_request_at = now;
	return ;
}

void Connection::set_m_wbuf_for_execute() { m_wbuf = m_request.get_m_content(); }
void Connection::set_m_wbuf_for_send(std::string wbuf_string) {
	if (wbuf_string.empty())
		m_wbuf = m_response.getString();
	else
		m_wbuf = wbuf_string;
	m_wbuf_data_size = m_wbuf.size(); 
	m_send_data_size = 0;
}
void Connection::set_m_status(Status status) { m_status = status; }
void Connection::set_m_token_size(int token_size) { m_token_size = token_size; }
void Connection::set_m_readed_size(int readed_size) { m_readed_size = readed_size; }
void Connection::set_m_is_cached(bool is_cached) { m_is_cached = is_cached; }
void Connection::set_m_is_filtered(bool is_filtered) { m_is_filtered = is_filtered; }
void Connection::set_m_rbuf_from_server(std::string rbuf_from_server) { m_rbuf_from_server = rbuf_from_server; }
void Connection::decreaseWbuf(int size) { m_wbuf.erase(0, size); }
void Connection::decreaseRbufFromClient(int size) { m_rbuf_from_client.erase(0, size); }
void Connection::addRbufFromClient(const char* str, int size) { m_rbuf_from_client.append(str, size); }
void Connection::addRbufFromServer(const char* str, int size) { m_rbuf_from_server.append(str, size); }
void Connection::clearRbufFromClient() { m_rbuf_from_client.clear(); }
void Connection::clearRbufFromServer() { m_rbuf_from_server.clear(); }
void Connection::clearWbuf() { m_wbuf.clear(); }
void Connection::set_m_server_fd(int fd) { m_server_fd = fd; }
void Connection::set_m_read_from_server_fd(int fd) { m_read_from_server_fd = fd; }
void Connection::set_m_write_to_server_fd(int fd) { m_write_to_server_fd = fd; }
void Connection::clear()
{
	m_status = ON_WAIT;
	m_server_fd = -1;
	m_read_from_server_fd = -1;
	m_write_to_server_fd = -1;
	m_request.clear();
	m_token_size = -1;
	m_readed_size = 0;
	m_response.clear();
	m_rbuf_from_server.clear();
	m_wbuf.clear();
	m_wbuf_data_size = 0;
	m_send_data_size = 0;
	m_is_filtered = false;
	m_is_cached = false;
}

void Connection::set_m_worker(Worker *worker) { m_worker = worker; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool Connection::isOverTime() const
{
	timeval now;

	if (gettimeofday(&now, NULL) == -1)
		throw std::runtime_error("gettimeofday error");
	long now_nbr = now.tv_sec + now.tv_usec / 1000000;
	long start_nbr = m_last_request_at.tv_sec + m_last_request_at.tv_usec / 1000000;
	return ((now_nbr - start_nbr) >= CONNECTION_OLD_SECOND);
}

bool
Connection::sendFromWbuf(int fd)
{
	int count = m_wbuf_data_size - m_send_data_size;
	if (count > BUFFER_SIZE)
		count = BUFFER_SIZE;
	count = send(fd, m_wbuf.c_str() + m_send_data_size, count, 0);
	if (count > 0)
		m_send_data_size += count;
	else
		return (false);
	return (true);
}

bool
Connection::isSendCompleted()
{	
	return (m_wbuf_data_size == m_send_data_size);
}
