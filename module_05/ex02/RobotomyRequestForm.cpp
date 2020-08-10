#include "RobotomyRequestForm.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

RobotomyRequestForm::RobotomyRequestForm() {}
RobotomyRequestForm::RobotomyRequestForm(const std::string& name, int required_sign_grade, int required_exec_grade, const std::string& target, /* constructor parameter */)
: Form(name, required_sign_grade, required_exec_grade, target), /* constructor initialize list */
{
	/* constructor code */
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
: Form(copy), /* copy-constructor initialize list */
{
	/* copy-constructor code */
	*this = copy;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

RobotomyRequestForm::~RobotomyRequestForm()
{
	/* destructor code */
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& obj)
{
	if (this == &obj)
		return (*this);
	this->Form::operator=(obj);
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const RobotomyRequestForm& robotomyRequestForm)
{
	out << /* write to what you print(RobotomyRequestForm.member) */ << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* getter code */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

