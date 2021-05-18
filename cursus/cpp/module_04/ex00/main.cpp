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
		print("SOCERER CONTRUCTOR CALL TEST");
		Sorcerer robert("Robert", "the Magnificent");
		print("SOCERER OVERLOAD TEST");
		std::cout << robert;
		print("VICTIM CONSTRUCTOR CALL TEST");
		Victim june("June");
		print("VICTIM ASSIGN CALL TEST");
		Victim anna = june;
		print("VICTIM ASSIGN OVERLOAD TEST");
		std::cout << anna;
		print("PEON CONSTRUCTOR CALL TEST");
		Peon zim("Zimmy");
		print("PEON COPY CONSTRUCTOR CALL TEST");
		Peon zimmy(zim);
		print("PEON COPY OVERLOAD TEST");
		std::cout << zimmy;
		print("POLYMORPH VICTIM");
		robert.polymorph(june);
		print("POLYMORPH PEON");
		robert.polymorph(zimmy);
		print("DESTRUCTOR CALL TEST...");
	}
	return (0);
}
