#include "Span.hpp"
#include <iostream>

void	print(std::string msg) {
	std::cout << std::endl
	<< "\033[1;37;41m" << msg << "\033[0m"
	<< std::endl << std::endl;
}

int main()
{
	print("DEFAULT_TEST");
	Span sp = Span(5);
	sp.addNumber(5);
	try {
		std::cout << sp.shortestSpan() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	try {
		sp.addNumber(15);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	print("ASSIGN_TEST");
	Span spTwo = Span(3);
	for (int i = 0; i < 3; i++)
		spTwo.addNumber(i * 10);
	try {
		spTwo.addNumber(4 * 10);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	sp = spTwo;
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	print("COPY_TEST");
	Span spThree(spTwo);
	std::cout << spThree.shortestSpan() << std::endl;
	std::cout << spThree.longestSpan() << std::endl;

	print("VECTOR ADD TEST");
	Span spFour(10);
	std::vector<int> intArr;
	for (int i = 0; i < 5; i++)
		spFour.addNumber((i + 1) * 10);
	for (int i = 6; i <= 9; i++)
		intArr.push_back(i * 10);
	intArr.push_back(90);
	spFour.addNumber(intArr.begin(), intArr.end());
	std::cout << spFour.shortestSpan() << std::endl;
	std::cout << spFour.longestSpan() << std::endl;
	print("TEST END");
}
