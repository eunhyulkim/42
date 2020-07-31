#ifndef SUPER_MUTANT_HPP
# define SUPER_MUTANT_HPP

# include <string>
# include <iostream>
# include "Enemy.hpp"

class SuperMutant : public Enemy
{
	public:
		SuperMutant();
		SuperMutant& operator=(const SuperMutant& obj);
		SuperMutant(const SuperMutant& copy);
		~SuperMutant();

		void takeDamage(int damage);
};

#endif
