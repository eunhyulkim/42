#ifndef PRESIDENTAL_PARDON_FORM_HPP
# define PRESIDENTAL_PARDON_FORM_HPP

# include <string>
# include <iostream>

# include "Form.hpp"

class PresidentalPardonForm : public Form
{
	private:
		/* declare member variable */
	public:
		PresidentalPardonForm();
		PresidentalPardonForm(const std::string& /* parameter */, ...);
		PresidentalPardonForm(const PresidentalPardonForm& copy);
		PresidentalPardonForm& operator=(const PresidentalPardonForm& obj);
		virtual ~PresidentalPardonForm();

		/* inherit overload code */
		void beExecuted();

		/* declare member function */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const PresidentalPardonForm& presidentalPardonForm);

#endif
