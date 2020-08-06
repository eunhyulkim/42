#include "Bureaucrat.hpp"

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string _name, int _grade)
: name(_name), grade(_grade)
{
	if (_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
: name(copy.getName()), grade(copy.getGrade()) {
	*this = copy;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::~Bureaucrat() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& obj)
{
	if (this == &obj)
		return (*this);
	this->name = obj.getName();
	this->grade = obj.getGrade();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Bureaucrat& Bureaucrat)
{
	out << Bureaucrat.getName() << "(" << Bureaucrat.getGrade() << ")";
	return (out);
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Bureaucrat::GradeTooHighException::GradeTooHighException() throw(){}
Bureaucrat::GradeTooHighException::GradeTooHighException(const Bureaucrat::GradeTooHighException&) throw(){}
Bureaucrat::GradeTooHighException& Bureaucrat::GradeTooHighException::operator=(const Bureaucrat::GradeTooHighException&) throw(){ return (*this); }
Bureaucrat::GradeTooHighException::~GradeTooHighException() throw(){}
const char* Bureaucrat::GradeTooHighException::what() const throw(){ return "GradeTooHighException error"; }

Bureaucrat::GradeTooLowException::GradeTooLowException() throw(){}
Bureaucrat::GradeTooLowException::GradeTooLowException(const Bureaucrat::GradeTooLowException&) throw(){}
Bureaucrat::GradeTooLowException& Bureaucrat::GradeTooLowException::operator=(const Bureaucrat::GradeTooLowException&) throw(){ return (*this); }
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw(){}
const char* Bureaucrat::GradeTooLowException::what() const throw(){ return "GradeTooLowException error"; }

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

const std::string&
Bureaucrat::getName(void) const
{
	return (this->name);
}

int
Bureaucrat::getGrade(void) const
{
	return (this->grade);
}

int
Bureaucrat::increment(void)
{
	if (this->grade - 1 > 0)
		this->grade -= 1;
	else
		throw GradeTooHighException();
	return (this->grade);
}

int
Bureaucrat::decrement(void)
{
	if (this->grade + 1 <= 150)
		this->grade += 1;
	else
		throw GradeTooLowException();
	return (this->grade);
}
