#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	// FragTrap a("HELLO");
	ScavTrap b("HI");

	// a.vaulthunter_dot_exe("OP");
	// a.vaulthunter_dot_exe("OP");
	// a.vaulthunter_dot_exe("OP");
	// a.vaulthunter_dot_exe("OP");
	// a.vaulthunter_dot_exe("OP");
	// a.takeDamage(24);
	// a.takeDamage(42);
	// a.beRepaired(24);
	// a.beRepaired(50);
	// a.beRepaired(30);
	// a.vaulthunter_dot_exe("OP");
	// a.takeDamage(36);
	// a.takeDamage(24);

	b.takeDamage(24);
	b.takeDamage(42);
	b.beRepaired(24);
	b.takeDamage(36);
	b.takeDamage(24);
	b.rangedAttack("YOU");
	b.rangedAttack("YOU");
	b.rangedAttack("YOU");
	b.rangedAttack("YOU");
	b.rangedAttack("YOU");
	b.rangedAttack("YOU");
	b.challengeNewcomer();
	b.challengeNewcomer();
	b.challengeNewcomer();
	b.challengeNewcomer();
	b.challengeNewcomer();

	return (0);
}
