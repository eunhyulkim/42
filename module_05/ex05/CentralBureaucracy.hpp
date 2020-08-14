#ifndef CENTRAL_BUREAUCRACY_HPP
# define CENTRAL_BUREAUCRACY_HPP

# include <string>
# include <iostream>
# include <random>

# include "Bureaucrat.hpp"
# include "Form.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "Intern.hpp"
# include "OfficeBlock.hpp"

class Bureaucrat;
class Form;
class PresidentialPardonForm;
class RobotomyRequestForm;
class ShrubberyCreationForm;
class Intern;
class OfficeBlock;

class CentralBureaucracy
{
	private:
		OfficeBlock m_office[20];
		Intern m_intern[20];
		int m_bureaucrat_count;
		int m_queue_count;
		std::string *m_queue;
	protected:
		CentralBureaucracy(const CentralBureaucracy&);
		CentralBureaucracy& operator=(const CentralBureaucracy&);
	public:
		CentralBureaucracy();
		virtual ~CentralBureaucracy();

		/* getter function */
		int get_m_bureaucrat_count() const;
		int get_m_queue_count() const;

		/* setter function */
		void set_m_bureaucrat_count(int bureaucrat_count);
		void set_m_queue_count(int queue_count);

		/* declare member function */
		void feed(const Bureaucrat& bureaucrat);
		void queueUp(const std::string& person);
		void doBureaucracy(void);

		/* exception declare */
		class FulledOfficeException : public std::exception {
			public:
				FulledOfficeException() throw ();
				FulledOfficeException(const FulledOfficeException&) throw ();
				FulledOfficeException& operator= (const FulledOfficeException&) throw ();
				virtual ~FulledOfficeException() throw ();
				virtual const char* what() const throw ();
		};

		class NobodyTargetException : public std::exception {
			public:
				NobodyTargetException() throw ();
				NobodyTargetException(const NobodyTargetException&) throw ();
				NobodyTargetException& operator= (const NobodyTargetException&) throw ();
				virtual ~NobodyTargetException() throw ();
				virtual const char* what() const throw ();
		};

		class EmptyOfficeException : public std::exception {
			public:
				EmptyOfficeException() throw ();
				EmptyOfficeException(const EmptyOfficeException&) throw ();
				EmptyOfficeException& operator= (const EmptyOfficeException&) throw ();
				virtual ~EmptyOfficeException() throw ();
				virtual const char* what() const throw ();
		};
};

/* global operator overload */
CentralBureaucracy &operator<<(CentralBureaucracy &central, const Bureaucrat& bureaucrat);
CentralBureaucracy &operator<<(CentralBureaucracy &central, const std::string& target);

#endif
