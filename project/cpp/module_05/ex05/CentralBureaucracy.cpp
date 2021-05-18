#include "CentralBureaucracy.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

CentralBureaucracy::CentralBureaucracy()
{
	this->m_bureaucrat_count = 0;
	this->m_queue_count = 0;
	this->m_queue = nullptr;
	for (int i = 0; i < 20; i++)
		this->m_office[i].set_m_intern(this->m_intern[i]);
}

CentralBureaucracy::CentralBureaucracy(const CentralBureaucracy&) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

CentralBureaucracy::~CentralBureaucracy()
{
	this->m_bureaucrat_count = 0;
	this->m_queue_count = 0;
	if (this->m_queue != nullptr)
	{
		delete[] this->m_queue;
		this->m_queue = nullptr;
	}
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

CentralBureaucracy& CentralBureaucracy::operator=(const CentralBureaucracy&) { return (*this); }

CentralBureaucracy&
operator<<(CentralBureaucracy &central, const Bureaucrat &bureaucrat)
{
	central.feed(bureaucrat);
	return (central);
}

CentralBureaucracy&
operator<<(CentralBureaucracy &central, const std::string &target)
{
	central.queueUp(target);
	return (central);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

int CentralBureaucracy::get_m_bureaucrat_count() const { return (this->m_bureaucrat_count); }
int CentralBureaucracy::get_m_queue_count() const { return (this->m_queue_count); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void CentralBureaucracy::set_m_bureaucrat_count(int bureaucrat_count) { this->m_bureaucrat_count = bureaucrat_count; }
void CentralBureaucracy::set_m_queue_count(int queue_count) { this->m_queue_count = queue_count; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

CentralBureaucracy::FulledOfficeException::FulledOfficeException() throw () : std::exception(){}
CentralBureaucracy::FulledOfficeException::FulledOfficeException(const FulledOfficeException&) throw () : std::exception(){}
CentralBureaucracy::FulledOfficeException& CentralBureaucracy::FulledOfficeException::operator=(const CentralBureaucracy::FulledOfficeException&) throw() { return (*this); }
CentralBureaucracy::FulledOfficeException::~FulledOfficeException() throw (){}
const char* CentralBureaucracy::FulledOfficeException::what() const throw () { return ("FulledOfficeException error"); }

CentralBureaucracy::NobodyTargetException::NobodyTargetException() throw () : std::exception(){}
CentralBureaucracy::NobodyTargetException::NobodyTargetException(const NobodyTargetException&) throw () : std::exception(){}
CentralBureaucracy::NobodyTargetException& CentralBureaucracy::NobodyTargetException::operator=(const CentralBureaucracy::NobodyTargetException&) throw() { return (*this); }
CentralBureaucracy::NobodyTargetException::~NobodyTargetException() throw (){}
const char* CentralBureaucracy::NobodyTargetException::what() const throw () { return ("NobodyTargetException error"); }

CentralBureaucracy::EmptyOfficeException::EmptyOfficeException() throw () : std::exception(){}
CentralBureaucracy::EmptyOfficeException::EmptyOfficeException(const EmptyOfficeException&) throw () : std::exception(){}
CentralBureaucracy::EmptyOfficeException& CentralBureaucracy::EmptyOfficeException::operator=(const CentralBureaucracy::EmptyOfficeException&) throw() { return (*this); }
CentralBureaucracy::EmptyOfficeException::~EmptyOfficeException() throw (){}
const char* CentralBureaucracy::EmptyOfficeException::what() const throw () { return ("EmptyOfficeException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */


void
CentralBureaucracy::feed(const Bureaucrat& bureaucrat) {
	if (this->m_bureaucrat_count >= 40)
		throw (CentralBureaucracy::FulledOfficeException());
	if (this->m_bureaucrat_count % 2 == 0)
		this->m_office[this->m_bureaucrat_count / 2].set_m_signer(const_cast<Bureaucrat&>(bureaucrat));
	else
		this->m_office[this->m_bureaucrat_count / 2].set_m_executor(const_cast<Bureaucrat&>(bureaucrat));
	this->set_m_bureaucrat_count(this->get_m_bureaucrat_count() + 1);
	return ;
}

void
CentralBureaucracy::queueUp(const std::string& person) {
	if (this->m_queue_count == 0)
	{
		this->m_queue = new std::string[1];
		this->m_queue[0] = person;
	}
	else
	{
		std::string *new_queue = new std::string[this->m_queue_count + 1];
		for (int i = 0; i < m_queue_count; i++)
			new_queue[i] = this->m_queue[i];
		new_queue[this->m_queue_count] = person;
		delete[] this->m_queue;
		this->m_queue = new_queue;
	}
	this->set_m_queue_count(this->get_m_queue_count() + 1);
	return ;
}

namespace {
	std::string get_random_request()
	{
		std::string option_list[]	=
		{
			"presidential pardon",
			"robotomy request",
			"shrubbery creation"
		};
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> request_dis(0, 2);
		return (option_list[request_dis(gen)]);
	}

	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

void
CentralBureaucracy::doBureaucracy(void) {
	if (this->m_queue_count == 0)
	{
		delete[] this->m_queue;
		this->m_queue = nullptr;
		this->set_m_queue_count(0);
		throw (CentralBureaucracy::NobodyTargetException());
	}
	if (this->m_bureaucrat_count < 2)
	{
		delete[] this->m_queue;
		this->m_queue = nullptr;
		this->set_m_queue_count(0);
		throw (CentralBureaucracy::EmptyOfficeException());
	}
	for (int i = 0; i < this->m_queue_count; i++)
	{
		print(this->m_queue[i] + " REQUEST START");
		bool executed = false;
		std::string request = get_random_request();
		for (int j = 0; j < (this->m_bureaucrat_count / 2); j++)
		{
			try {
				this->m_office[j].doBureaucracy(request, this->m_queue[i]);
				executed = true;
				break ;
			} catch (std::exception& e) {
				std::cout << "\033[1m[office " << j << "]\033[0m Go somewhere else Because we have " << e.what() << std::endl;
				continue ;
			}
		}
		if (executed == false)
			std::cout << "Sorry, but it's hard for " << this->m_queue[i] << "\'s request to be resolved." << std::endl;
	}

	delete[] this->m_queue;
	this->m_queue = nullptr;
	this->set_m_queue_count(0);
}
