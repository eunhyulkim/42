#include "ServerManager.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::ServerManager()
{
    this->m_max_fd = 0;
    FD_ZERO(&m_read_set);
    FD_ZERO(&m_read_copy_set);
    FD_ZERO(&m_write_set);
    FD_ZERO(&m_write_copy_set);
    FD_ZERO(&m_error_set);
    FD_ZERO(&m_error_copy_set);
}

ServerManager::ServerManager(const ServerManager& copy) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::~ServerManager()
{
    this->m_max_fd = 0;
    FD_ZERO(&m_read_set);
    FD_ZERO(&m_read_copy_set);
    FD_ZERO(&m_write_set);
    FD_ZERO(&m_write_copy_set);
    FD_ZERO(&m_error_set);
    FD_ZERO(&m_error_copy_set);
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ServerManager& ServerManager::operator=(const ServerManager& obj)
{
	if (this == &obj)
		return (*this);
	return (*this);
}

namespace
{
	void
	printFdSet(fd_set s, int max_fd)
	{
		bool first = true;
		for (int i = 0; i <= max_fd; ++i)
		{
			if (FD_ISSET(i, &s))
			{
				if (!first) {
					std::cout << " ";
				}
				first = false;
				std::cout << i;
			}
		}
	}
}

void ServerManager::printFdSets()
{
	std::cout << "MAX_FD: " << this->m_max_fd << std::endl;
	std::cout << "[SET_ERROR_FD]" << std::endl;
	printFdSet(this->m_error_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_ERROR_COPY_FD]" << std::endl;
	printFdSet(this->m_error_copy_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_READ_FD]" << std::endl;
	printFdSet(this->m_read_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_READ_COPY_FD]" << std::endl;
	printFdSet(this->m_read_copy_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_WRITE_FD]" << std::endl;
	printFdSet(this->m_write_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_WRITE_COPY_FD]" << std::endl;
	printFdSet(this->m_write_copy_set, this->m_max_fd); std::cout << std::endl;
	return ;
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

Config ServerManager::get_m_config() const { return (this->m_config); }
int ServerManager::get_m_max_fd() const { return (this->m_max_fd); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void ServerManager::set_m_max_fd(int max_fd) { this->m_max_fd = max_fd; }
void ServerManager::set_m_config(const Config& config) { this->m_config = config; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void ServerManager::fdSet(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		FD_SET(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_SET(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_SET(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_SET(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_SET(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_SET(fd, &this->m_error_copy_set);
}

void ServerManager::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET)
		FD_ZERO(&this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_ZERO(&this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_ZERO(&this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_ZERO(&this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_ZERO(&this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_ZERO(&this->m_error_copy_set);
}

void ServerManager::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		FD_CLR(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_CLR(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_CLR(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_CLR(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_CLR(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_CLR(fd, &this->m_error_copy_set);
}

bool ServerManager::fdIsset(int fd, SetType fdset)
{
	bool ret = false;

	if (fdset == WRITE_SET)
		ret = FD_ISSET(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ret = FD_ISSET(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ret = FD_ISSET(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ret = FD_ISSET(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		ret = FD_ISSET(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		ret = FD_ISSET(fd, &this->m_error_copy_set);
	return (ret);
}

void ServerManager::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET) {
		FD_ZERO(&this->m_write_copy_set);
		this->m_write_copy_set = this->m_write_set;
	} else if (fdset == READ_SET) {
		FD_ZERO(&this->m_read_copy_set);
		this->m_read_copy_set = this->m_read_set;
	} else if (fdset == ERROR_SET) {
		FD_ZERO(&this->m_error_copy_set);
		this->m_error_copy_set = this->m_error_set;
	}
}
