#include "FragTrap.hpp"

typedef void	(FragTrap::* func_member)(std::string const &);

FragTrap::FragTrap(char const *name) {
	this->Name = std::string(name);
	this->HitPoints = 100;
	this->MaxHitPoints = 100;
	this->EnergyPoints = 100;
	this->MaxEnergyPoints = 100;
	this->Level = 1;
	this->JurorsAttackDamage = 50;
	this->MeleeAttackDamage = 30;
	this->RangedAttackDamage = 20;
	this->MiddlesAttackDamage = 10;
	this->HeatersAttackDamage = 5;
	this->ArmorDamageReduction = 5;
	std::cout << "[FR4G-TP-CONS] FragTrap" << std::endl;
}

FragTrap::FragTrap() {
	this->Name = std::string("anonymous");
	this->HitPoints = 100;
	this->MaxHitPoints = 100;
	this->EnergyPoints = 100;
	this->MaxEnergyPoints = 100;
	this->Level = 1;
	this->JurorsAttackDamage = 50;
	this->MeleeAttackDamage = 30;
	this->RangedAttackDamage = 20;
	this->MiddlesAttackDamage = 10;
	this->HeatersAttackDamage = 5;
	this->ArmorDamageReduction = 5;
	std::cout << "[FR4G-TP-CONS] FragTrap" << std::endl;
}

FragTrap&
FragTrap::operator=(const FragTrap& obj) {
	if (this != &obj)
	{
		this->Name = obj.Name;
		this->HitPoints = obj.HitPoints;
		this->MaxHitPoints = obj.MaxHitPoints;
		this->EnergyPoints = obj.EnergyPoints;
		this->MaxEnergyPoints = obj.MaxEnergyPoints;
		this->Level = obj.Level;
		this->JurorsAttackDamage = obj.JurorsAttackDamage;
		this->MeleeAttackDamage = obj.MeleeAttackDamage;
		this->RangedAttackDamage = obj.RangedAttackDamage;
		this->MiddlesAttackDamage = obj.MiddlesAttackDamage;
		this->HeatersAttackDamage = obj.HeatersAttackDamage;
		this->ArmorDamageReduction = obj.ArmorDamageReduction;
	}
	return (*this);
}

FragTrap::FragTrap(const FragTrap& copy) {
	*this = copy;
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
FragTrap::meleeAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mmelee\033[0;47;30m"
	<< ", causing \033[1m" << this->MeleeAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
FragTrap::rangedAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mranged\033[0;47;30m"
	<< ", causing \033[1m" << this->RangedAttackDamage
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

void
FragTrap::takeDamage(unsigned int amount) {
	amount -= this->ArmorDamageReduction;
	if (amount > this->HitPoints)
		amount = this->HitPoints;
	this->HitPoints -= amount;
	std::cout << "[FR4G-TP] \033[41;37m'" << this->Name << "' take damage \033[1m"
	<< amount << " points\033[0;41;37m, remain HitPoints is \033[1m"
	<< this->HitPoints << " points!\033[0m" << std::endl;
}

void
FragTrap::beRepaired(unsigned int amount) {
	int		HpAmount = amount;
	int		EnergyAmount = amount;

	if (this->HitPoints + amount > 100)
		HpAmount = 100 - this->HitPoints;
	if (this->EnergyPoints + amount > 100)
		EnergyAmount = 100 - this->EnergyPoints;
	this->HitPoints += HpAmount;
	this->EnergyPoints += EnergyAmount;
	std::cout << "[FR4G-TP] \033[46;37m'" << this->Name << "' beRepaired. "
	<< "remain HitPoints(Energy) is \033[1m"
	<< this->HitPoints << "(" << this->EnergyPoints << ") points!\033[0m" << std::endl;
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
