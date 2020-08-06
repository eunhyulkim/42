#include "Bureaucrat.hpp"
#include "Form.hpp"

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::Form() {}
Form::Form(const std::string& name, int sign_grade, int execute_grade)
: _name(name), _signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
	if (sign_grade < 1 || execute_grade < 1)
		throw Form::GradeTooHighException();
	if (sign_grade > 150 || execute_grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form& copy)
: _name(copy.getName()), _signed(copy.getSigned()),
_sign_grade(copy.getSignGrade()), _execute_grade(copy.getExecuteGrade()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::~Form() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Form& Form::operator=(const Form& obj)
{
	if (this == &obj)
		return (*this);
	this->_name = obj.getName();
	this->_signed = obj.getSigned();
	this->_sign_grade = obj.getSignGrade();
	this->_execute_grade = obj.getExecuteGrade();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Form& form)
{
	out << "<" << form.getName() << ">" << " form is";
	if (!form.getSigned())
		out << " not";
	out << " signed, sign-grade is " << form.getSignGrade() << ", ";
	out << "execute-grade is " << form.getExecuteGrade() << ".";
	return (out);
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Form::GradeTooHighException::GradeTooHighException() throw(){}
Form::GradeTooHighException::GradeTooHighException(const Form::GradeTooHighException&) throw(){}
Form::GradeTooHighException& Form::GradeTooHighException::operator=(const Form::GradeTooHighException&) throw(){ return (*this); }
Form::GradeTooHighException::~GradeTooHighException() throw(){}
const char* Form::GradeTooHighException::what() const throw(){ return "GradeTooHighException error"; }

Form::GradeTooLowException::GradeTooLowException() throw(){}
Form::GradeTooLowException::GradeTooLowException(const Form::GradeTooLowException&) throw(){}
Form::GradeTooLowException& Form::GradeTooLowException::operator=(const Form::GradeTooLowException&) throw(){ return (*this); }
Form::GradeTooLowException::~GradeTooLowException() throw(){}
const char* Form::GradeTooLowException::what() const throw(){ return "GradeTooLowException error"; }

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

const std::string Form::getName() const { return (this->_name); }
bool Form::getSigned() const { return (this->_signed); }
int Form::getSignGrade() const { return (this->_sign_grade); }
int Form::getExecuteGrade() const { return (this->_execute_grade); }

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->_sign_grade)
		throw Form::GradeTooLowException();
	else if (this->_signed == true)
		throw ("form is already signed.");
	else
		this->_signed = true;
}
