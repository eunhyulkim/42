#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int		main(void)
{
/* 
** 	EX03 TEST
*/
	print("CREATE FORM SUCCESSFUL");
	Intern noname;
	Form *pform = noname.makeForm("presidential pardon", "killer");
	Form *rform = noname.makeForm("robotomy request", "human");
	Form *sform = noname.makeForm("shrubbery creation", "summer");

	print("CREATE FORM FAILURE");
	Form *xform = noname.makeForm("Presidential pardon", "killer");
	(void)xform;

	delete pform;
	delete rform;
	delete sform;
	print("TEST_END");
	return (0);
}
