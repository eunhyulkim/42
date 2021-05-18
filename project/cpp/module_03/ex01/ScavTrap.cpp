#include "ScavTrap.hpp"

typedef void	(ScavTrap::* func_member)(void);

ScavTrap::ScavTrap(std::string name) {
	this->Name = name;
	this->HitPoints = 100;
	this->MaxHitPoints = 100;
	this->EnergyPoints = 50;
	this->MaxEnergyPoints = 50;
	this->Level = 1;
	this->JurorsAttackDamage = 30;
	this->MeleeAttackDamage = 20;
	this->RangedAttackDamage = 15;
	this->MiddlesAttackDamage = 7;
	this->HeatersAttackDamage = 3;
	this->ArmorDamageReduction = 3;
	std::cout << "[FR4G-TP-CONS] ScavTrap" << std::endl;
}

ScavTrap::ScavTrap() {
	this->Name = std::string("noname");
	this->HitPoints = 100;
	this->MaxHitPoints = 100;
	this->EnergyPoints = 50;
	this->MaxEnergyPoints = 50;
	this->Level = 1;
	this->JurorsAttackDamage = 30;
	this->MeleeAttackDamage = 20;
	this->RangedAttackDamage = 15;
	this->MiddlesAttackDamage = 7;
	this->HeatersAttackDamage = 3;
	this->ArmorDamageReduction = 3;
	std::cout << "[FR4G-TP-CONS] ScavTrap" << std::endl;
}

ScavTrap&
ScavTrap::operator=(const ScavTrap& obj) {
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

ScavTrap::ScavTrap(const ScavTrap& copy) {
	*this = copy;
}

ScavTrap::~ScavTrap() {
	std::cout << "[FR4G-TP-DES] ScavTrap" << std::endl;
}


/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

void
ScavTrap::meleeAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mmelee\033[0;47;30m"
	<< ", causing \033[1m" << this->MeleeAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
ScavTrap::rangedAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mranged\033[0;47;30m"
	<< ", causing \033[1m" << this->RangedAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
	if (this->EnergyPoints > 10)
		this->EnergyPoints -= 10;
	else
		this->EnergyPoints = 0;
}

void
ScavTrap::jurorsChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "The jurors appear vaguely stranded and at loose ends, uprooted from their routines and livelihoods."
	<< "\033[0m" << std::endl;
	this->EnergyPoints += 5;
}

void
ScavTrap::middlesChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "I like middles ... It is in middles that extremes clash, where ambiguity restlessly rules."
	<< "\033[0m" << std::endl;
	this->EnergyPoints += 3;
}

void
ScavTrap::heatersChallenge(void) {
	std::cout << "[FR4G-TP] \033[37;42m"
	<< "I love 'Heathers', and I loved doing that movie. I'm very proud of it, so if it gets brought up, I'm happy."
	<< "\033[0m" << std::endl;
	this->EnergyPoints += 7;
}

void
ScavTrap::takeDamage(unsigned int amount) {
	amount -= this->ArmorDamageReduction;
	if (amount > this->HitPoints)
		amount = this->HitPoints;
	this->HitPoints -= amount;
	std::cout << "[FR4G-TP] \033[41;37m'" << this->Name << "' take damage \033[1m"
	<< amount << " points\033[0;41;37m, remain HitPoints is \033[1m"
	<< this->HitPoints << " points!\033[0m" << std::endl;
}

void
ScavTrap::beRepaired(unsigned int amount) {
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
		&ScavTrap::jurorsChallenge,
		&ScavTrap::middlesChallenge, &ScavTrap::heatersChallenge
	};

	int get_random_challenge_id(void)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> challenge_dis(0, 2);
		return (challenge_dis(gen));
	}

}

void
ScavTrap::challengeNewcomer(void) {
	if (this->EnergyPoints > 25)
	{
		std::cout << "[FR4G-TP-ERORR] energy is too much. challenge is not for you." << std::endl;
		return ;
	}
	(this->*member[get_random_challenge_id()])();
}
