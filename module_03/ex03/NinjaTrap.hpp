#ifndef NINJA_TRAP_HPP
# define NINJA_TRAP_HPP

#include <iostream>
#include <string>
#include <random>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class NinjaTrap : public ClapTrap {
	public:
		NinjaTrap(std::string name);
		NinjaTrap();
		~NinjaTrap();
		NinjaTrap(const NinjaTrap& copy);
		NinjaTrap& operator=(const NinjaTrap& obj);
		void ninjaShoebox(FragTrap& fragTrap);
		void ninjaShoebox(ScavTrap& scavTrap);
		void ninjaShoebox(NinjaTrap& ninjaTrap);
		void shadowStep(void);
		std::string getHitPoints(void);
};
#endif
