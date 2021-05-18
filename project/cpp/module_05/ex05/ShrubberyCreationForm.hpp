#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include <string>
# include <iostream>
# include <fstream>

# include "Bureaucrat.hpp"
# include "Form.hpp"

class Bureaucrat;
class Form;

class ShrubberyCreationForm : public Form
{
	private:
		ShrubberyCreationForm();
	public:
		ShrubberyCreationForm(const std::string& target);
		ShrubberyCreationForm(const ShrubberyCreationForm& copy);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& obj);
		virtual ~ShrubberyCreationForm();

		/* inherit overload function */
		virtual void beExecuted(const Bureaucrat&) const;

		/* declare member function */
};

/* global operator overload */

#endif
