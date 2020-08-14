#ifndef OFFICE_BLOCK_HPP
# define OFFICE_BLOCK_HPP

# include <string>
# include <iostream>
# include "Bureaucrat.hpp"
# include "Form.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "Intern.hpp"

class Bureaucrat;
class Form;
class PresidentialPardonForm;
class RobotomyRequestForm;
class ShrubberyCreationForm;
class Intern;

class OfficeBlock
{
	private:
		Bureaucrat const *m_signer;
		Bureaucrat const *m_executor;
		Intern const *m_intern;
		OfficeBlock(const OfficeBlock&);
		OfficeBlock& operator=(const OfficeBlock&);
	public:
		OfficeBlock();
		OfficeBlock(Bureaucrat& signer, Bureaucrat& executor, Intern& intern);
		virtual ~OfficeBlock();

		/* setter function */
		void set_m_intern(Intern const &intern);
		void set_m_signer(Bureaucrat const &signer);
		void set_m_executor(Bureaucrat const &executor);

		/* declare member function */
		void doBureaucracy(const std::string& form_name, const std::string& target);

		/* exception declare */
		class GradeTooLowException : public std::exception {
			public:
				GradeTooLowException() throw ();
				GradeTooLowException(const GradeTooLowException&) throw ();
				GradeTooLowException& operator= (const GradeTooLowException&) throw ();
				virtual ~GradeTooLowException() throw ();
				virtual const char* what() const throw ();
		};

		class NotFilledBlockException : public std::exception {
			public:
				NotFilledBlockException() throw ();
				NotFilledBlockException(const NotFilledBlockException&) throw ();
				NotFilledBlockException& operator= (const NotFilledBlockException&) throw ();
				virtual ~NotFilledBlockException() throw ();
				virtual const char* what() const throw ();
		};
		
		class FailedMakeFormException : public std::exception {
			public:
				FailedMakeFormException() throw ();
				FailedMakeFormException(const FailedMakeFormException&) throw ();
				FailedMakeFormException& operator= (const FailedMakeFormException&) throw ();
				virtual ~FailedMakeFormException() throw ();
				virtual const char* what() const throw ();
		};
};

/* global operator overload */

#endif
