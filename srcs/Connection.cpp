#include "Connection.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Connection::Connection() {}
Connection::Connection(int fd, const std::string& client_ip, int client_port)
: m_client_fd(fd), m_client_ip(client_ip)
{
	this->m_last_request_at.tv_sec = 0;
	this->m_last_request_at.tv_usec = 0;
	this->m_client_port = client_port;
	set_m_last_request_at();
}

Connection::Connection(const Connection& copy)
: m_client_fd(copy.get_m_client_fd()), m_last_request_at(copy.get_m_last_request_at()), \
m_client_ip(copy.get_m_client_ip()), m_client_port(copy.get_m_client_port()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Connection::~Connection()
{
	this->m_client_fd = 0;
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
	this->m_client_fd = obj.get_m_client_fd();
	this->m_last_request_at = obj.get_m_last_request_at();
	this->m_client_ip = obj.get_m_client_ip();
	this->m_client_port = obj.get_m_client_port();
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

int Connection::get_m_client_fd() const { return (this->m_client_fd); }
timeval Connection::get_m_last_request_at() const { return (this->m_last_request_at); }
std::string Connection::get_m_client_ip() const { return (this->m_client_ip); }
int Connection::get_m_client_port() const { return (this->m_client_port); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Connection::set_m_last_request_at()
{
	timeval now;
	if (gettimeofday(&now, reinterpret_cast<struct timezone *>(NULL)) == -1)
		return ;
	this->m_last_request_at = now;
	return ;
}

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
	
	long now_nbr = now.tv_sec * 1000 + now.tv_usec;
	long start_nbr = m_last_request_at.tv_sec * 1000 + m_last_request_at.tv_usec;
	
	return ((now_nbr - start_nbr) / 1000 >= CONNECTION_OLD);
}
