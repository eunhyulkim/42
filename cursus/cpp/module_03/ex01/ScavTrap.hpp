#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include <iostream>
#include <string>
#include <random>

class ScavTrap {
	private:
		std::string Name;
		int HitPoints;
		int MaxHitPoints;
		int EnergyPoints;
		int MaxEnergyPoints;
		int Level;
		int JurorsAttackDamage;
		int MeleeAttackDamage;
		int RangedAttackDamage;
		int MiddlesAttackDamage;
		int HeatersAttackDamage;
		int ArmorDamageReduction;
	public:
		ScavTrap(std::string name);
		ScavTrap();
		~ScavTrap();
		ScavTrap(const ScavTrap& copy);
		ScavTrap& operator=(const ScavTrap& obj);

		void meleeAttack(std::string const & target);
		void rangedAttack(std::string const & target);
		void jurorsChallenge(void);
		void middlesChallenge(void);
		void heatersChallenge(void);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		void challengeNewcomer(void);
};
#endif
