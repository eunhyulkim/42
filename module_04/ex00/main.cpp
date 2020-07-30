#include "Victim.hpp"
#include "Peon.hpp"
#include "Sorcerer.hpp"

# define BASIC_TEST		true

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}

	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	if (BASIC_TEST)
	{
		print("TEST : EXPECT SAME RESULT WITH CASE");
		Sorcerer robert("Robert", "the Magnificent");
		Victim	 jim("Jimmy");
		Peon	 joe("Joe");

		std::cout << robert << jim << joe;

		robert.polymorph(jim);
		robert.polymorph(joe);
	}
	else
	{
		print("TEST : 3 Peon Virth and Death (Expect 12 Lines)");
		Peon	zim("Zimmy");
		Peon	zoe(zim);
		Peon	robert("Robert");
		robert = zim;
	}
	return (0);
}
