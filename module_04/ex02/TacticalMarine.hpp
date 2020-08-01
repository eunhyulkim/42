#ifndef TACTICAL_MARINE_HPP
# define TACTICAL_MARINE_HPP

#include "ISpaceMarine.hpp"
#include <iostream>

class TacticalMarine : public ISpaceMarine
{
	public:
		TacticalMarine();
		~TacticalMarine();
		TacticalMarine(const TacticalMarine& copy);
		TacticalMarine& operator=(const TacticalMarine& obj);

		ISpaceMarine* clone(void) const;
		void battleCry(void) const;
		void rangedAttack(void) const;
		void meleeAttack(void) const;
};

#endif
