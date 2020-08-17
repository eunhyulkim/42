#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		std::string m_name;
		bool m_signed;
		int m_required_sign_grade;
		int m_required_exec_grade;
		Form();
	public:
		Form(const std::string& name, int sign_grade, int exec_grade);
		Form(const Form& copy);
		Form& operator=(const Form& obj);
		virtual ~Form();

		/* getter function */
		std::string get_m_name() const;
		bool get_m_signed() const;
		int get_m_required_sign_grade() const;
		int get_m_required_exec_grade() const;

		/* declare member function */
		void beSigned(const Bureaucrat& Bureaucrat);

		/* exception declare */
		class GradeTooLowException : public std::exception {
			public:
				GradeTooLowException() throw ();
				GradeTooLowException(const GradeTooLowException&) throw ();
				GradeTooLowException& operator= (const GradeTooLowException&) throw ();
				virtual ~GradeTooLowException() throw ();
				virtual const char* what() const throw ();
		};

		class GradeTooHighException : public std::exception {
			public:
				GradeTooHighException() throw ();
				GradeTooHighException(const GradeTooHighException&) throw ();
				GradeTooHighException& operator= (const GradeTooHighException&) throw ();
				virtual ~GradeTooHighException() throw ();
				virtual const char* what() const throw ();
		};
		
		class AlreadySignedException : public std::exception {
			public:
				AlreadySignedException() throw ();
				AlreadySignedException(const AlreadySignedException&) throw ();
				AlreadySignedException& operator= (const AlreadySignedException&) throw ();
				virtual ~AlreadySignedException() throw ();
				virtual const char* what() const throw ();
		};
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Form& form);

#endif
