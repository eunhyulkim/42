#include <iostream>
#include "Fixed.class.hpp"

int main( void ) {
	Fixed a(10);
	Fixed b(-10);
	Fixed c(1);
	Fixed d(-1);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	return 0;
}