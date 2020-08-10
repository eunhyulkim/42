#include "Form.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::Form() {}
Form::Form(const std::string& name, int required_sign_grade, int required_exec_grade, const std::string& target)
: name(name), _required_sign_grade(required_sign_grade), _required_exec_grade(required_exec_grade), _target(target)
{
	this->_signed = false;
}

Form::Form(const Form& copy)
: name(copy.getName()), _required_sign_grade(copy.getRequired_sign_grade()), _required_exec_grade(copy.getRequired_exec_grade()), _target(copy.getTarget())
{
	this->_signed = false;
	*this = copy;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Form::~Form()
{
	this->name.clear();
	this->_signed = false;
	this->_required_sign_grade = 0;
	this->_required_exec_grade = 0;
	this->_target.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Form& Form::operator=(const Form& obj)
{
	if (this == &obj)
		return (*this);
	this->name = obj.getName();
	this->_signed = obj.getSigned();
	this->_required_sign_grade = obj.getRequired_sign_grade();
	this->_required_exec_grade = obj.getRequired_exec_grade();
	this->_target = obj.getTarget();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Form& form)
{
	out << /* write to what you print(Form.member) */ << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Form::getName() const { return (this->name); }
bool Form::getSigned() const { return (this->_signed); }
int Form::getRequired_sign_grade() const { return (this->_required_sign_grade); }
int Form::getRequired_exec_grade() const { return (this->_required_exec_grade); }
std::string Form::getTarget() const { return (this->_target); }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Form::GradeTooHighException::GradeTooHighException() throw (){}
Form::GradeTooHighException::GradeTooHighException(const GradeTooHighException&) throw (){}
Form::GradeTooHighException& Form::GradeTooHighException::operator=(const Form::GradeTooHighException&) throw() { return (*this); }
Form::GradeTooHighException::~GradeTooHighException() throw (){}
const char* Form::GradeTooHighException::what() const throw () { return ("GradeTooHighException error"); }

Form::GradeTooLowException::GradeTooLowException() throw (){}
Form::GradeTooLowException::GradeTooLowException(const GradeTooLowException&) throw (){}
Form::GradeTooLowException& Form::GradeTooLowException::operator=(const Form::GradeTooLowException&) throw() { return (*this); }
Form::GradeTooLowException::~GradeTooLowException() throw (){}
const char* Form::GradeTooLowException::what() const throw () { return ("GradeTooLowException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Form::beSigned(const Bureaucrat& bureaucrat) {
	/* function body */
}

void
Form::beExecuted() {
	/* function body */
}
