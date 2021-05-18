#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include <string>
# include <iostream>
# include <random>

# include "Bureaucrat.hpp"
# include "Form.hpp"

class Bureaucrat;
class Form;

class RobotomyRequestForm : public Form
{
	private:
		RobotomyRequestForm();
	public:
		RobotomyRequestForm(const std::string& target);
		RobotomyRequestForm(const RobotomyRequestForm& copy);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& obj);
		virtual ~RobotomyRequestForm();

		/* inherit overload function */
		virtual void beExecuted(const Bureaucrat&) const;

		/* declare member function */
};

/* global operator overload */

#endif
