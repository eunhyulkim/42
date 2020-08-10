#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include <string>
# include <iostream>

# include "Form.hpp"

class RobotomyRequestForm : public Form
{
	private:
		/* declare member variable */
	public:
		RobotomyRequestForm();
		RobotomyRequestForm(const std::string& /* parameter */, ...);
		RobotomyRequestForm(const RobotomyRequestForm& copy);
		RobotomyRequestForm& operator=(const RobotomyRequestForm& obj);
		virtual ~RobotomyRequestForm();

		/* inherit overload code */
		void beExecuted();

		/* declare member function */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const RobotomyRequestForm& robotomyRequestForm);

#endif
