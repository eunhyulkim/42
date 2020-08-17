#ifndef TACTICAL_MARINE_HPP
# define TACTICAL_MARINE_HPP

# include <string>
# include <iostream>

# include "ISpaceMarine.hpp"

class TacticalMarine : public ISpaceMarine
{
	public:
		TacticalMarine();
		TacticalMarine(const TacticalMarine&);
		TacticalMarine& operator=(const TacticalMarine& obj);
		virtual ~TacticalMarine();

		/* inherit overload function */
		virtual ISpaceMarine* clone() const;
		virtual void battleCry() const;
		virtual void rangedAttack() const;
		virtual void meleeAttack() const;
};

#endif
