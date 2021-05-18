#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "Bureaucrat.hpp"

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int		main(void)
{
	print("BASIC + UNDERFLOW TEST(2->1->0)");
	try {
			Bureaucrat c("kim", 2);
			std::cout << c << std::endl;
			c.upGrade();
			std::cout << c << std::endl;
			c.upGrade();
			std::cout << c << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	print("BASIC + OVERFLOW TEST(149->150->151)");
	try {
		Bureaucrat c("eunh", 149);
		std::cout << c << std::endl;
		c.downGrade();
		std::cout << c << std::endl;
		c.downGrade();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	print("TEST_END");
	return (0);
}
