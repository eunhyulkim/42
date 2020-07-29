#include "NinjaTrap.hpp"

typedef void	(NinjaTrap::* func_member)(std::string const &);

NinjaTrap::NinjaTrap(char const *name) : ClapTrap(name, 60, 120, 60, 5, 0)
{
	std::cout << "[FR4G-TP-CONS] NinjaTrap" << std::endl;
}

NinjaTrap::NinjaTrap(const NinjaTrap& copy) : ClapTrap(copy) {
	std::cout << "[FR4G-TP-COPY] NinjaTrap" << std::endl;
}

NinjaTrap&
NinjaTrap::operator=(const NinjaTrap& obj) {
	this->ClapTrap::operator=(obj);
	std::cout << "[FR4G-TP-ASSIGN] NinjaTrap" << std::endl;
	return (*this);
}

NinjaTrap::~NinjaTrap() {
	std::cout << "[FR4G-TP-DES] NinjaTrap" << std::endl;
}

/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

void
NinjaTrap::shadowStep(void)
{
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' step shadow..."
	<< "\033[0m" << std::endl;
}

void
NinjaTrap::ninjaShoebox(FragTrap& fragTrap)
{
	fragTrap.vaulthunter_dot_exe("FRAG-TARGET");
}

void
NinjaTrap::ninjaShoebox(ScavTrap& scavTrap)
{
	scavTrap.challengeNewcomer();
}

void
NinjaTrap::ninjaShoebox(NinjaTrap& ninjaTrap)
{
	ninjaTrap.shadowStep();
}
