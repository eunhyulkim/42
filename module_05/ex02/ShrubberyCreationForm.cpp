#include "ShrubberyCreationForm.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ShrubberyCreationForm::ShrubberyCreationForm() {}
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& name, int required_sign_grade, int required_exec_grade, const std::string& target, /* constructor parameter */)
: Form(name, required_sign_grade, required_exec_grade, target), /* constructor initialize list */
{
	/* constructor code */
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy)
: Form(copy), /* copy-constructor initialize list */
{
	/* copy-constructor code */
	*this = copy;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	/* destructor code */
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& obj)
{
	if (this == &obj)
		return (*this);
	this->Form::operator=(obj);
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const ShrubberyCreationForm& shrubberyCreationForm)
{
	out << /* write to what you print(ShrubberyCreationForm.member) */ << std::endl;
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

