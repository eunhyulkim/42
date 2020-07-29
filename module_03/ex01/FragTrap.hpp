#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include <iostream>
#include <string>
#include <random>

class FragTrap {
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
		FragTrap(char const *name);
		FragTrap();
		~FragTrap();
		FragTrap(const FragTrap& copy);
		FragTrap& operator=(const FragTrap& obj);

		void jurorsAttack(std::string const & target);
		void meleeAttack(std::string const & target);
		void rangedAttack(std::string const & target);
		void middlesAttack(std::string const & target);
		void heatersAttack(std::string const & target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		void vaulthunter_dot_exe(std::string const & target);
};
#endif
