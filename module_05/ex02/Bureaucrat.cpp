#include "Bureaucrat.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string& name, int grade)
: _name(name), _grade(grade)
{
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();	
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
: _name(copy.getName()), _grade(copy.getGrade())
{
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->_grade > 150)
		throw Bureaucrat::GradeTooLowException();	
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Bureaucrat::~Bureaucrat()
{
	this->_name.clear();
	this->_grade = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& obj)
{
	if (this == &obj)
		return (*this);
	this->_name = obj.getName();
	this->_grade = obj.getGrade();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	out << Bureaucrat.getName() << "(" << Bureaucrat.getGrade() << ")" << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Bureaucrat::getName() const { return (this->_name); }
int Bureaucrat::getGrade() const { return (this->_grade); }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Bureaucrat::GradeTooHighException::GradeTooHighException() throw (){}
Bureaucrat::GradeTooHighException::GradeTooHighException(const GradeTooHighException&) throw (){}
Bureaucrat::GradeTooHighException& Bureaucrat::GradeTooHighException::operator=(const Bureaucrat::GradeTooHighException&) throw() { return (*this); }
Bureaucrat::GradeTooHighException::~GradeTooHighException() throw (){}
const char* Bureaucrat::GradeTooHighException::what() const throw () { return ("GradeTooHighException error"); }

Bureaucrat::GradeTooLowException::GradeTooLowException() throw (){}
Bureaucrat::GradeTooLowException::GradeTooLowException(const GradeTooLowException&) throw (){}
Bureaucrat::GradeTooLowException& Bureaucrat::GradeTooLowException::operator=(const Bureaucrat::GradeTooLowException&) throw() { return (*this); }
Bureaucrat::GradeTooLowException::~GradeTooLowException() throw (){}
const char* Bureaucrat::GradeTooLowException::what() const throw () { return ("GradeTooLowException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
void
Bureaucrat::upGrade() {
	if (this->grade - 1 > 0)
		this->grade -= 1;
	else
		throw GradeTooHighException();
	return (this->grade);
}

void
Bureaucrat::downGrade() {
	if (this->grade + 1 <= 150)
		this->grade += 1;
	else
		throw GradeTooLowException();
	return (this->grade);
}

void
Bureaucrat::signForm(Form& form) {
	std::cout << this->name;
	try {
		form.beSigned(*this);
		std::cout << " signs " << form.getName() << std::endl;
	} catch (std::exception& e) {
		std::cout << " cannot sign " << form.getName() << " because ";
		std::cout << "bureaucrat grade is too low." << std::endl;
	} catch (char const *reason) {
		std::cout << " cannot sign " << form.getName() << " because ";
		std::cout << reason << std::endl;
	}
}

void
Bureaucrat::executeForm(const Form& form) {
	/* function body */
}
