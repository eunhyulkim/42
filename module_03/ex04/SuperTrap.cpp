#include "SuperTrap.hpp"

typedef void	(NinjaTrap::* func_member)(std::string const &);

SuperTrap::SuperTrap(char const *name) \
: ClapTrap(name, 100, 120, 60, 20, 5), FragTrap(name), NinjaTrap(name)
{
	std::cout << "[FR4G-TP-CONS] SuperTrap" << std::endl;
}

SuperTrap::SuperTrap(const SuperTrap& copy) : FragTrap(copy), NinjaTrap() {
	std::cout << "[FR4G-TP-COPY] SuperTrap" << std::endl;
}

SuperTrap&
SuperTrap::operator=(const SuperTrap& obj) {
	this->FragTrap::operator=(obj);
	this->NinjaTrap::operator=(obj);
	std::cout << "[FR4G-TP-ASSIGN] SuperTrap" << std::endl;
	return (*this);
}

SuperTrap::~SuperTrap() {
	std::cout << "[FR4G-TP-DES] SuperTrap" << std::endl;
}

/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

void
SuperTrap::meleeAttack(std::string const & target) {
	this->NinjaTrap::meleeAttack(target);
}

void
SuperTrap::rangedAttack(std::string const & target) {
	this->FragTrap::rangedAttack(target);
}


void
SuperTrap::getStatus(void) {
	std::cout << "[STATUS]" << std::endl;
	std::cout << "Name: " << this->Name << std::endl;
	std::cout << "HitPoints: " << this->HitPoints << std::endl;
	std::cout << "MaxHitPoints: " << this->MaxHitPoints << std::endl;
	std::cout << "EnergyPoints: " << this->EnergyPoints << std::endl;
	std::cout << "MaxEnergyPoints: " << this->MaxEnergyPoints << std::endl;
	std::cout << "Level: " << this->Level << std::endl;
	std::cout << "MeleeAttackDamage: " << this->MeleeAttackDamage << std::endl;
	std::cout << "RangedAttackDamage: " << this->RangedAttackDamage << std::endl;
	std::cout << "ArmorDamageReduction: " << this->ArmorDamageReduction << std::endl;
};
