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
		Bureaucrat *m_signer;
		Bureaucrat *m_executor;
		Intern *m_intern;
		OfficeBlock(const OfficeBlock&);
		OfficeBlock& operator=(const OfficeBlock&);
	public:
		OfficeBlock();
		OfficeBlock(Bureaucrat& signer, Bureaucrat& executor, Intern& intern);
		virtual ~OfficeBlock();

		/* getter function */
		Bureaucrat *get_m_signer() const;
		Bureaucrat *get_m_executor() const;
		Intern *get_m_intern() const;

		/* setter function */
		void set_m_intern(Intern& intern);
		void set_m_signer(Bureaucrat& signer);
		void set_m_executor(Bureaucrat& executor);

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
		
		class ForbiddenMultiException : public std::exception {
			public:
				ForbiddenMultiException() throw ();
				ForbiddenMultiException(const ForbiddenMultiException&) throw ();
				ForbiddenMultiException& operator= (const ForbiddenMultiException&) throw ();
				virtual ~ForbiddenMultiException() throw ();
				virtual const char* what() const throw ();
		};

		class FulledInBlockException : public std::exception {
			public:
				FulledInBlockException() throw ();
				FulledInBlockException(const FulledInBlockException&) throw ();
				FulledInBlockException& operator= (const FulledInBlockException&) throw ();
				virtual ~FulledInBlockException() throw ();
				virtual const char* what() const throw ();
		};
};

/* global operator overload */

#endif
