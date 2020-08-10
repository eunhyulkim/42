#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include <string>
# include <iostream>

# include "Form.hpp"

class ShrubberyCreationForm : public Form
{
	private:
		/* declare member variable */
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string& /* parameter */, ...);
		ShrubberyCreationForm(const ShrubberyCreationForm& copy);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& obj);
		virtual ~ShrubberyCreationForm();

		/* inherit overload code */
		void beExecuted();

		/* declare member function */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const ShrubberyCreationForm& shrubberyCreationForm);

#endif
