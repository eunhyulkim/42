#ifndef SUPER_TRAP_HPP
# define SUPER_TRAP_HPP

#include <iostream>
#include <string>
#include <random>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "NinjaTrap.hpp"

class SuperTrap : virtual protected ClapTrap, public FragTrap, public NinjaTrap {
	public:
		SuperTrap(std::string name);
		SuperTrap();
		~SuperTrap();
		SuperTrap(const SuperTrap& copy);
		SuperTrap& operator=(const SuperTrap& obj);

		void meleeAttack(std::string const & target);
		void rangedAttack(std::string const & target);
		void getStatus(void);
};
#endif
