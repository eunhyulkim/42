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
Intern::makeForm(const std::string& form, const std::string& target) {
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
	std::cout << "Intern failed to create " << form << ". that is unvalid form name." << std::endl;
	return (created_form);
}
