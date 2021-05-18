/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:10:47 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/31 13:02:56 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name, int HitPoints, int EnergyPoints, \
int MeleeAttackDamage, int RangedAttackDamage, int ArmorDamageReduction)
{
	this->Name = name;
	this->HitPoints = HitPoints;
	this->MaxHitPoints = HitPoints;
	this->EnergyPoints = EnergyPoints;
	this->MaxEnergyPoints = EnergyPoints;
	this->Level = 1;
	this->MeleeAttackDamage = MeleeAttackDamage;;
	this->RangedAttackDamage = RangedAttackDamage;;
	this->ArmorDamageReduction = ArmorDamageReduction;
	std::cout << "[FR4G-TP-CONS] ClapTrap" << std::endl;
}

ClapTrap::ClapTrap()
{
	this->Name = std::string("noname");
	this->HitPoints = 0;
	this->MaxHitPoints = 0;
	this->EnergyPoints = 0;
	this->MaxEnergyPoints = 0;
	this->Level = 0;
	this->MeleeAttackDamage = 0;
	this->RangedAttackDamage = 0;
	this->ArmorDamageReduction = 0;
	std::cout << "[FR4G-TP-CONS] ClapTrap" << std::endl;
}

ClapTrap&
ClapTrap::operator=(const ClapTrap& obj) {
	if (this != &obj)
	{
		this->Name = obj.Name;
		this->HitPoints = obj.HitPoints;
		this->MaxHitPoints = obj.MaxHitPoints;
		this->EnergyPoints = obj.EnergyPoints;
		this->MaxEnergyPoints = obj.MaxEnergyPoints;
		this->Level = obj.Level;
		this->MeleeAttackDamage = obj.MeleeAttackDamage;
		this->RangedAttackDamage = obj.RangedAttackDamage;
		this->ArmorDamageReduction = obj.ArmorDamageReduction;
	}
	return (*this);
}

ClapTrap::ClapTrap(const ClapTrap& copy) {
	*this = copy;
}

ClapTrap::~ClapTrap() {
	std::cout << "[FR4G-TP-DES] ClapTrap" << std::endl;
}


/*
** FR4G-TP <name> attacks <target> at range, causing <damage> points of damage!
*/

void
ClapTrap::meleeAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mmelee\033[0;47;30m"
	<< ", causing \033[1m" << this->MeleeAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
ClapTrap::rangedAttack(std::string const & target){
	std::cout << "[FR4G-TP] \033[47;30m'" << this->Name << "' attacks '"
	<< target << "' at " << "\033[1mranged\033[0;47;30m"
	<< ", causing \033[1m" << this->RangedAttackDamage
	<< " points \033[0;47;30mof damage!\033[0m" << std::endl;
}

void
ClapTrap::takeDamage(unsigned int amount) {
	amount -= this->ArmorDamageReduction;
	if (amount > this->HitPoints)
		amount = this->HitPoints;
	this->HitPoints -= amount;
	std::cout << "[FR4G-TP] \033[41;37m'" << this->Name << "' take damage \033[1m"
	<< amount << " points\033[0;41;37m, remain HitPoints is \033[1m"
	<< this->HitPoints << " points!\033[0m" << std::endl;
}

void
ClapTrap::beRepaired(unsigned int amount) {
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

void
ClapTrap::getStatus(void) {
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
