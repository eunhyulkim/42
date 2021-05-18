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

# define DEBUG_LEVEL	2
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
** 	EX02 TEST
*/
	if (DEBUG_LEVEL <= 2)
	{
		print("CREATE FORM");
		PresidentialPardonForm a("Killer");
		std::cout << a << std::endl;
		RobotomyRequestForm b("human");
		std::cout << b << std::endl;
		ShrubberyCreationForm c("summer");
		std::cout << c << std::endl;

		print("CREATE BUREAUCRAT");
		Bureaucrat d("elite", 5);
		Bureaucrat e("senior", 45);
		Bureaucrat f("junior", 72);
		Bureaucrat g("internA", 137);
		Bureaucrat h("internA", 145);
		std::cout << d << std::endl;
		std::cout << e << std::endl;
		std::cout << f << std::endl;
		std::cout << g << std::endl;
		std::cout << h << std::endl;

		print("SIGN FAIL TEST(GRADE_TOO_LOW)");
		e.signForm(a);
		g.signForm(b);

		print("EXECUTE FAIL TEST(NOT_SIGNED)");
		e.executeForm(a);
		g.executeForm(b);

		print("SIGN SUCCESS TEST");
		d.signForm(a);
		f.signForm(b);
		h.signForm(c);

		print("SIGN FAIL TEST(ALREADY_SIGNED)");
		d.signForm(a);
		f.signForm(b);
		h.signForm(c);

		print("EXECUTE FAIL TEST(GRADE_TOO_LOW)");
		e.executeForm(a);
		f.executeForm(b);
		h.executeForm(c);

		print("EXECUTE SUCCESS TEST");
		d.executeForm(a);
		e.executeForm(b);
		g.executeForm(c);
	}
	print("TEST_END");
	return (0);
}
