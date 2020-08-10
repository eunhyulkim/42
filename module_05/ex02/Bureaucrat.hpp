#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <iostream>

class Bureaucrat
{
	private:
		std::string _name;
		int _grade;
		Bureaucrat();
	public:
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat& operator=(const Bureaucrat& obj);
		virtual ~Bureaucrat();

		/* getter function */
		std::string getName() const;
		int getGrade() const;

		/* declare member function */
		void upGrade();
		void downGrade();
		void signForm(Form& form);
		void executeForm(const Form& form);

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
std::ostream&	operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif
