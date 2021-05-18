#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include <iostream>
#include <string>
#include <random>

class FragTrap {
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
		FragTrap(std::string name);
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
