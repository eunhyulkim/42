#include "Human.hpp"

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

int		main(void)
{
	Human t;

	print("MELEE ATTACK TEST");
	t.action("meleeAttack", "opponent1");
	print("RANGED ATTACK TEST");
	t.action("rangedAttack", "opponent2");
	print("INTIMIDATING SHOUT TEST");
	t.action("intimidatingShout", "opponent3");
	print("NOT FIND ACTION TEST");
	t.action("Anonymous Action", "opponent4");
	return (0);
}
