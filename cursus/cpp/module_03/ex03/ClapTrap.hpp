#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <iostream>
#include <string>
#include <random>

class ClapTrap {
	protected:
		std::string Name;
		int HitPoints;
		int MaxHitPoints;
		int EnergyPoints;
		int MaxEnergyPoints;
		int Level;
		int MeleeAttackDamage;
		int RangedAttackDamage;
		int ArmorDamageReduction;
	public:
		ClapTrap(std::string name, int HitPoints, int EnergyPoints, \
		int MeleeAttackDamage, int RangedAttackDamage, int ArmorDamageReduction);
		ClapTrap();
		~ClapTrap();
		ClapTrap(const ClapTrap& copy);
		ClapTrap& operator=(const ClapTrap& obj);

		void meleeAttack(std::string const & target);
		void rangedAttack(std::string const & target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		void getStatus(void);
};
#endif
