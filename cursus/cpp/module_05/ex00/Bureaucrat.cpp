#include "Bureaucrat.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string& name, int grade)
: m_name(name), m_grade(grade)
{
	if (m_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (m_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
: m_name(copy.get_m_name()), m_grade(copy.get_m_grade()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::~Bureaucrat() {
	this->m_grade = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& obj)
{
	if (this == &obj)
		return (*this);
	this->m_grade = obj.get_m_grade();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	out << bureaucrat.get_m_name();
	out << "(" << bureaucrat.get_m_grade();
	out << ")";
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Bureaucrat::get_m_name() const { return (this->m_name); }
int Bureaucrat::get_m_grade() const { return (this->m_grade); }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Bureaucrat::GradeTooLowException::GradeTooLowException() throw () : std::exception(){}
Bureaucrat::GradeTooLowException::GradeTooLowException(const GradeTooLowException&) throw () : std::exception(){}
Bureaucrat::GradeTooLowException& Bureaucrat::GradeTooLowException::operator=(const Bureaucrat::GradeTooLowException&) throw() { return (*this); }
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw (){}
const char* Bureaucrat::GradeTooLowException::what() const throw () { return ("GradeTooLowException error"); }

Bureaucrat::GradeTooHighException::GradeTooHighException() throw () : std::exception(){}
Bureaucrat::GradeTooHighException::GradeTooHighException(const GradeTooHighException&) throw () : std::exception(){}
Bureaucrat::GradeTooHighException& Bureaucrat::GradeTooHighException::operator=(const Bureaucrat::GradeTooHighException&) throw() { return (*this); }
Bureaucrat::GradeTooHighException::~GradeTooHighException() throw (){}
const char* Bureaucrat::GradeTooHighException::what() const throw () { return ("GradeTooHighException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Bureaucrat::upGrade(void) {
	if (this->m_grade - 1 > 0)
		this->m_grade -= 1;
	else
		throw Bureaucrat::GradeTooHighException();
}

void
Bureaucrat::downGrade(void) {
	if (this->m_grade + 1 <= 150)
		this->m_grade += 1;
	else
		throw Bureaucrat::GradeTooLowException();
}
