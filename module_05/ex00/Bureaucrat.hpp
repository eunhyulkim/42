#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <iostream>

class Bureaucrat
{
	private:
		std::string name;
		int grade;
		Bureaucrat();
	public:
		Bureaucrat(const std::string name, int grade);
		Bureaucrat(const Bureaucrat& copy);
		Bureaucrat& operator=(const Bureaucrat& obj);

		const std::string& getName(void) const;
		int getGrade(void) const;
		int increment(void);
		~Bureaucrat();
		int decrement(void);

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

std::ostream&	operator<<(std::ostream& out, const Bureaucrat& Bureaucrat);

#endif
