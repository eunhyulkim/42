#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <iostream>
# include "Bureaucrat.hpp"

class Form
{
	private:
		std::string		_name;
		bool			_signed;
		int				_sign_grade;
		int				_execute_grade;
		Form();

	public:
		Form(const std::string& name, int sign_grade, int excute_grade);
		Form(const Form& copy);
		Form& operator=(const Form& obj);
		virtual ~Form();

		const std::string getName() const;
		bool getSigned() const;
		int getSignGrade() const;
		int getExecuteGrade() const;

		void beSigned(const Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				GradeTooHighException() throw();
				GradeTooHighException(const GradeTooHighException&) throw();
				GradeTooHighException& operator=(const GradeTooHighException&) throw();
				virtual ~GradeTooHighException() throw();
				virtual const char* what() const throw();
			};

		class GradeTooLowException : public std::exception {
			public:
				GradeTooLowException() throw();
				GradeTooLowException(const GradeTooLowException&) throw();
				GradeTooLowException& operator=(const GradeTooLowException&) throw();
				virtual ~GradeTooLowException() throw();
				virtual const char* what() const throw();
			};
};

std::ostream&	operator<<(std::ostream& out, const Form& Form);

#endif
