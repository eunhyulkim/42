#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Bureaucrat.hpp"
#include "Form.hpp"

# define DEBUG_LEVEL	1
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
** 	EX00 TEST
*/
	if (DEBUG_LEVEL <= 0)
	{
		print("BASIC + UNDERFLOW TEST(2->1->0)");
		try {
				Bureaucrat c("kim", 2);
				std::cout << c << std::endl;
				c.increment();
				std::cout << c << std::endl;
				c.increment();
				std::cout << c << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		print("BASIC + OVERFLOW TEST(149->150->151)");
		try {
			Bureaucrat c("eunh", 149);
			std::cout << c << std::endl;
			c.decrement();
			std::cout << c << std::endl;
			c.decrement();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

/*
** 	EX01 TEST
*/
	if (DEBUG_LEVEL <= 1)
	{
		print("CREAT FORM SUCCESS CASE");
		Form a("normal-form", 1, 150);
		print("CREAT FORM FAILURE CASE");
		try {
			Form b("normal-form", 0, 150);
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		try {
			Form b("normal-form", 1, 151);
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		print("FORM SIGN SUCCESS CASE");
		Bureaucrat c("star-c", 1);
		c.signForm(a);
		print("FORM SIGN FAILURE CASE");
		c.signForm(a);
		Bureaucrat d("star-d", 9);
		d.signForm(a);
		print("FORM OVERLOAD TEST");
		std::cout << a << std::endl;
	}
	print("TEST_END");
	return (0);
}
