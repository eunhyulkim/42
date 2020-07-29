#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

# define DEBUG	true

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	FragTrap a("FragQ");
	ScavTrap b("ScavQ");

	if (DEBUG)
	{
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

		print("BASIC TEST : 1 REPAIRED(MAX 100)");
		a.vaulthunter_dot_exe("OP");
	}

	print("BASIC TEST : 2 RANDOM ATTACK");
	b.takeDamage(24);
	b.takeDamage(42);

	print("BASIC TEST : 1 REPAIRED");
	b.beRepaired(24);

	print("BASIC TEST : 2 TAKE DAMAGE");
	b.takeDamage(36);
	b.takeDamage(24);

	print("BASIC TEST : 2 MELEE ATTACK");
	b.meleeAttack("A");
	b.meleeAttack("B");

	print("BASIC TEST : 4 RANGED ATTACK");
	b.rangedAttack("C");
	b.rangedAttack("D");
	b.rangedAttack("E");
	b.rangedAttack("F");

	print("FAIL TEST : 1 CHALLENGE(ENERGY)");
	b.challengeNewcomer();

	print("BASIC TEST : 2 RANGED ATTACK");
	b.rangedAttack("G");
	b.rangedAttack("H");

	print("SUCCESS OR FAIL TEST : 4 CHALLENGE(ENERGY)");
	b.challengeNewcomer();
	b.challengeNewcomer();
	b.challengeNewcomer();
	b.challengeNewcomer();

	print("TEST END");
	return (0);
}
