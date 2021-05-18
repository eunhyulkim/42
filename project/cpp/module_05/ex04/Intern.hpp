#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>
# include <iostream>

# include "Form.hpp"
# include "Bureaucrat.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"

class Bureaucrat;
class Form;
class PresidentialPardonForm;
class RobotomyRequestForm;
class ShrubberyCreationForm;

class Intern
{
	private:
	public:
		Intern();
		Intern(const Intern&);
		Intern& operator=(const Intern&);
		virtual ~Intern();

		/* declare member function */
		Form* makeForm(const std::string& form, const std::string& target);
		/* exception declare */
		
		class FailedMakeFormException : public std::exception {
			public:
				FailedMakeFormException() throw ();
				FailedMakeFormException(const FailedMakeFormException&) throw ();
				FailedMakeFormException& operator= (const FailedMakeFormException&) throw ();
				virtual ~FailedMakeFormException() throw ();
				virtual const char* what() const throw ();
		};
};

struct FormType
{
	std::string type;
	Form *(*make)(std::string);
};

/* global operator overload */

#endif
