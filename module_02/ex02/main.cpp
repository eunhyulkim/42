#include <iostream>
#include "Fixed.class.hpp"

int main( void ) {
	Fixed a(1.11f);
	Fixed a2(1.11f);
	Fixed b(1.22f);
	Fixed c(10);

	std::cout << "a: 1.11f -> " << a << std::endl;
	std::cout << "b: 1.22f -> " << b << std::endl;
	std::cout << "c: 10 -> " << c << std::endl;
	
	std::cout << "a + b = " << (a + b) << std::endl;
	std::cout << "b - a = " << (b - a) << std::endl;
	std::cout << "b * c = " << b * c << std::endl;
	std::cout << "b / c = " << b / c << std::endl;

	std::cout << "false-> " << std::boolalpha << (a > b) << std::endl;
	std::cout << "false-> " << std::boolalpha << (a >= b) << std::endl;
	std::cout << "true-> " << std::boolalpha << (a >= a2) << std::endl;
	std::cout << "true-> " << std::boolalpha << (a < b) << std::endl;
	std::cout << "true-> " << std::boolalpha << (a <= a2) << std::endl;
	std::cout << "false-> " << std::boolalpha << (a == b) << std::endl;
	std::cout << "true-> " << std::boolalpha << (a == a2) << std::endl;
	std::cout << "true-> " << std::boolalpha << (a != b) << std::endl;
	std::cout << "false-> " << std::boolalpha << (a != a2) << std::endl;
	return 0;
}
