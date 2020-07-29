#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include <iostream>
#include <string>
#include <random>

class ScavTrap {
	private:
		std::string Name; // Parameter of constructor
		int HitPoints; // 100
		int MaxHitPoints; // 100
		int EnergyPoints; // 100
		int MaxEnergyPoints; // 100
		int Level; // 1
		int JurorsAttackDamage; // 50
		int MeleeAttackDamage; // 30
		int RangedAttackDamage; // 20
		int MiddlesAttackDamage; // 10
		int HeatersAttackDamage; // 5
		int ArmorDamageReduction; // 5
	public:
		ScavTrap(char const *name);
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
