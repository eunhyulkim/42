#include "RobotomyRequestForm.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

RobotomyRequestForm::RobotomyRequestForm() {}
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
: Form("Robotomy Request Form", 72, 45, target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
: Form(copy) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

RobotomyRequestForm::~RobotomyRequestForm() {}

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

std::string
get_random_result_fifty()
{
	std::string option_list[]	=
	{
		"success",
		"fail"
	};
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> result_fifty_dis(0, 1);
	return (option_list[result_fifty_dis(gen)]);
}

void
RobotomyRequestForm::beExecuted(const Bureaucrat&) const {
		std::cout << *this << " has ";
	if (get_random_result_fifty() == "success")
		std::cout << "been robotomized successfully" << std::endl;
	else
		std::cout << "not been robotomized failure" << std::endl;

}

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

