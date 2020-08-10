#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <iostream>

class Form
{
	private:
		std::string name;
		bool		_signed;
		int			_required_sign_grade;
		int			_required_exec_grade;
		std::string _target;
		Form();
	public:
		Form(const std::string& name, int required_sign_grade, int required_exec_grade, const std::string& target);
		Form(const Form& copy);
		Form& operator=(const Form& obj);
		virtual ~Form();

		/* getter function */
		std::string getName() const;
		bool getSigned() const;
		int getRequired_sign_grade() const;
		int getRequired_exec_grade() const;
		std::string getTarget() const;

		/* declare member function */
		void beSigned(const Bureaucrat& bureaucrat);
		virtual void beExecuted();

		/* exception declare */
		class GradeTooHighException : public std::exception {
			public:
				GradeTooHighException() throw ();
				GradeTooHighException(const GradeTooHighException&) throw ();
				GradeTooHighException& operator= (const GradeTooHighException&) throw ();
				virtual ~GradeTooHighException() throw ();
				virtual const char* what() const throw ();
		};

		class GradeTooLowException : public std::exception {
			public:
				GradeTooLowException() throw ();
				GradeTooLowException(const GradeTooLowException&) throw ();
				GradeTooLowException& operator= (const GradeTooLowException&) throw ();
				virtual ~GradeTooLowException() throw ();
				virtual const char* what() const throw ();
		};
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Form& form);

#endif
