#include "FragTrap.hpp"

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	FragTrap a("TYO");

	print("BASIC TEST : 4 RANDOM ATTACK");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");

	print("FAIL TEST : 1 RANDOM ATTACK(ENERGY)");
	a.vaulthunter_dot_exe("OP");

	print("BASIC TEST : 2 TAKE DAMAGE");
	a.takeDamage(24);
	a.takeDamage(42);

	print("BASIC TEST : 2 REPAIRED");
	a.beRepaired(24);
	a.beRepaired(50);

	print("OVERFLOW TEST : 1 REPAIRED(MAX 100)");
	a.beRepaired(30);

	print("BASIC TEST : 1 RE-ATTACK");
	a.vaulthunter_dot_exe("OP");

	print("TEST END");
	return (0);
}
