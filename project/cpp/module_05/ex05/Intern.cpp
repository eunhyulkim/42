#include "Intern.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Intern::Intern() {}
Intern::Intern(const Intern&) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Intern::~Intern() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Intern& Intern::operator=(const Intern&) { return (*this); }

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Intern::FailedMakeFormException::FailedMakeFormException() throw () : std::exception(){}
Intern::FailedMakeFormException::FailedMakeFormException(const FailedMakeFormException&) throw () : std::exception(){}
Intern::FailedMakeFormException& Intern::FailedMakeFormException::operator=(const Intern::FailedMakeFormException&) throw() { return (*this); }
Intern::FailedMakeFormException::~FailedMakeFormException() throw (){}
const char* Intern::FailedMakeFormException::what() const throw () { return ("FailedMakeFormException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

namespace {
	Form *makeShrubbery(std::string target) {
		return new ShrubberyCreationForm(target);
	}

	Form *makeRobotomy(std::string target) {
		return new RobotomyRequestForm(target);
	}

	Form *makePardon(std::string target) {
		return new PresidentialPardonForm(target);
	}
	
	struct FormType types[3] = {
		{ "shrubbery creation", makeShrubbery },
		{ "robotomy request", makeRobotomy },
		{ "presidential pardon", makePardon }
	};
}

Form*
Intern::makeForm(const std::string& form, const std::string& target) const {
	Form *created_form = nullptr;

	for (int i = 0; i < 3; i++)
	{
		if (types[i].type == form)
		{
			created_form = (types[i].make)(target);
			std::cout << "Intern creates " << *created_form << std::endl;
			return (created_form);
		}
	}
	throw (Intern::FailedMakeFormException());
	return (created_form);
}
