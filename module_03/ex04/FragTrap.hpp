#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include <iostream>
#include <string>
#include <random>
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
	protected:
		int JurorsAttackDamage;
		int MiddlesAttackDamage;
		int HeatersAttackDamage;
	public:
		FragTrap(char const *name);
		FragTrap();
		~FragTrap();
		FragTrap(const FragTrap& copy);
		FragTrap& operator=(const FragTrap& obj);

		void meleeAttack(std::string const & target);
		void rangedAttack(std::string const & target);
		void jurorsAttack(std::string const & target);
		void middlesAttack(std::string const & target);
		void heatersAttack(std::string const & target);
		void vaulthunter_dot_exe(std::string const & target);
		void getStatus(void);
};
#endif
