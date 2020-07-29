#include "FragTrap.hpp"

int main(void)
{
	FragTrap a("HELLO");

	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.vaulthunter_dot_exe("OP");
	a.takeDamage(24);
	a.takeDamage(42);
	a.beRepaired(24);
	a.beRepaired(50);
	a.beRepaired(30);
	a.vaulthunter_dot_exe("OP");
	a.takeDamage(36);
	a.takeDamage(24);
	return (0);
}
