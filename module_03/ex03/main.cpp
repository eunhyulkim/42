#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"

int main(void)
{
	FragTrap a("HELLO");
	ScavTrap b("HI");
	NinjaTrap c("NIN");

	c.ninjaShoebox(a);
	c.ninjaShoebox(b);
	c.ninjaShoebox(c);

	return (0);
}
