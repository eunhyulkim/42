#include "FragTrap.hpp"

typedef void	(FragTrap::* func_member)(std::string const &);

FragTrap::FragTrap(std::string name) : ClapTrap(name, 100, 30, 20, 5)
{
	this->JurorsAttackDamage = 50;
	this->MiddlesAttackDamage = 25;
	this->HeatersAttackDamage = 10;
	std::cout << "[FR4G-TP-CONS] FragTrap" << std::endl;
}

FragTrap::FragTrap() : ClapTrap()
{
	this->JurorsAttackDamage = 0;
	this->MiddlesAttackDamage = 0;
	this->HeatersAttackDamage = 0;
	std::cout << "[FR4G-TP-CONS] FragTrap" << std::endl;
}

FragTrap::FragTrap(const FragTrap& copy) : ClapTrap(copy) {
	this->JurorsAttackDamage = copy.JurorsAttackDamage;
	this->MiddlesAttackDamage = copy.MiddlesAttackDamage;
	this->HeatersAttackDamage = copy.HeatersAttackDamage;
}

FragTrap&
FragTrap::operator=(const FragTrap& obj) {
	this->ClapTrap::operator=(obj);
	this->JurorsAttackDamage = obj.JurorsAttackDamage;
	this->MiddlesAttackDamage = obj.MiddlesAttackDamage;
	this->HeatersAttackDamage = obj.HeatersAttackDamage;
	return (*this);
}


FragTrap::~FragTrap() {
	std::cout << "[FR4G-TP-DES] FragTrap" << std::endl;
}

/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

void
FragTrap::jurorsAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mjours\033[0;47;30m"
	<< ", causing \033[1m" << this->JurorsAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
FragTrap::middlesAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mmiddle\033[0;47;30m"
	<< ", causing \033[1m" << this->MiddlesAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
FragTrap::heatersAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mheaters\033[0;47;30m"
	<< ", causing \033[1m" << this->HeatersAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

namespace {
	func_member	member[5] = {
		&FragTrap::meleeAttack, &FragTrap::rangedAttack, &FragTrap::jurorsAttack,
		&FragTrap::middlesAttack, &FragTrap::heatersAttack
	};

	int get_random_attack_id(void)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> attack_dis(0, 4);
		return (attack_dis(gen));
	}
}

void
FragTrap::vaulthunter_dot_exe(std::string const & target) {
	if (this->EnergyPoints < 25)
	{
		std::cout << "[FR4G-TP-ERORR] energy is not enough" << std::endl;
		return ;
	}
	this->EnergyPoints -= 25;
	(this->*member[get_random_attack_id()])(target);
}

void
FragTrap::getStatus(void) {
	std::cout << "[STATUS]" << std::endl;
	std::cout << "Name: " << this->Name << std::endl;
	std::cout << "HitPoints: " << this->HitPoints << std::endl;
	std::cout << "MaxHitPoints: " << this->MaxHitPoints << std::endl;
	std::cout << "EnergyPoints: " << this->EnergyPoints << std::endl;
	std::cout << "MaxEnergyPoints: " << this->MaxEnergyPoints << std::endl;
	std::cout << "Level: " << this->Level << std::endl;
	std::cout << "MeleeAttackDamage: " << this->MeleeAttackDamage << std::endl;
	std::cout << "RangedAttackDamage: " << this->RangedAttackDamage << std::endl;
	std::cout << "JurorsAttackDamage: " << this->JurorsAttackDamage << std::endl;
	std::cout << "MiddlesAttackDamage: " << this->MiddlesAttackDamage << std::endl;
	std::cout << "HeatersAttackDamage: " << this->HeatersAttackDamage << std::endl;
	std::cout << "ArmorDamageReduction: " << this->ArmorDamageReduction << std::endl;
};
