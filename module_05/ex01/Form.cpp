#include "Form.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::Form() {}
Form::Form(const std::string& name, int sign_grade, int exec_grade)
: m_name(name), m_required_sign_grade(sign_grade), m_required_exec_grade(exec_grade)
{
	if (sign_grade > 150 || exec_grade > 150)
		throw Form::GradeTooLowException();
	if (sign_grade <= 0 || exec_grade <= 0)
		throw Form::GradeTooHighException();
	this->m_signed = false;
}

Form::Form(const Form& copy)
: m_name(copy.get_m_name()), 
m_required_sign_grade(copy.get_m_required_sign_grade()), 
m_required_exec_grade(copy.get_m_required_exec_grade())
{
	this->m_signed = false;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::~Form()
{
	this->m_signed = false;
	this->m_required_sign_grade = 0;
	this->m_required_exec_grade = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Form& Form::operator=(const Form& obj)
{
	if (this == &obj)
		return (*this);
	this->m_name = obj.get_m_name();
	this->m_signed = obj.get_m_signed();
	this->m_required_sign_grade = obj.get_m_required_sign_grade();
	this->m_required_exec_grade = obj.get_m_required_exec_grade();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Form& form)
{
	out << "<" << form.get_m_name();
	out << "(signed: " << std::boolalpha << form.get_m_signed();
	out << ", require_sign_grade(" << form.get_m_required_sign_grade();
	out << "), required_exec_grade(" << form.get_m_required_exec_grade() << ")>";
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Form::get_m_name() const { return (this->m_name); }
bool Form::get_m_signed() const { return (this->m_signed); }
int Form::get_m_required_sign_grade() const { return (this->m_required_sign_grade); }
int Form::get_m_required_exec_grade() const { return (this->m_required_exec_grade); }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Form::GradeTooLowException::GradeTooLowException() throw () : std::exception(){}
Form::GradeTooLowException::GradeTooLowException(const GradeTooLowException&) throw () : std::exception(){}
Form::GradeTooLowException& Form::GradeTooLowException::operator=(const Form::GradeTooLowException&) throw() { return (*this); }
Form::GradeTooLowException::~GradeTooLowException() throw (){}
const char* Form::GradeTooLowException::what() const throw () { return ("GradeTooLowException error"); }

Form::GradeTooHighException::GradeTooHighException() throw () : std::exception(){}
Form::GradeTooHighException::GradeTooHighException(const GradeTooHighException&) throw () : std::exception(){}
Form::GradeTooHighException& Form::GradeTooHighException::operator=(const Form::GradeTooHighException&) throw() { return (*this); }
Form::GradeTooHighException::~GradeTooHighException() throw (){}
const char* Form::GradeTooHighException::what() const throw () { return ("GradeTooHighException error"); }

Form::AlreadySignedException::AlreadySignedException() throw () : std::exception(){}
Form::AlreadySignedException::AlreadySignedException(const AlreadySignedException&) throw () : std::exception(){}
Form::AlreadySignedException& Form::AlreadySignedException::operator=(const Form::AlreadySignedException&) throw() { return (*this); }
Form::AlreadySignedException::~AlreadySignedException() throw (){}
const char* Form::AlreadySignedException::what() const throw () { return ("AlreadySignedException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.get_m_grade() > this->m_required_sign_grade)
		throw Form::GradeTooLowException();
	else if (this->m_signed == true)
		throw Form::AlreadySignedException();
	else
		this->m_signed = true;
}
