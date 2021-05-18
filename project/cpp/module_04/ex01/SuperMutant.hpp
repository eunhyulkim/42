#ifndef SUPER_MUTANT_HPP
# define SUPER_MUTANT_HPP

# include <string>
# include <iostream>

# include "Enemy.hpp"

class SuperMutant : public Enemy
{
	public:
		SuperMutant();
		SuperMutant(const SuperMutant& copy);
		SuperMutant& operator=(const SuperMutant& obj);
		virtual ~SuperMutant();

		/* inherit overload function */
		virtual void takeDamage(int damage);

		/* declare member function */
};

/* global operator overload */

#endif
