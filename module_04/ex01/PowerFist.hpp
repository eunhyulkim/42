#ifndef POWER_FIST_HPP
# define POWER_FIST_HPP

# include <string>
# include <iostream>

# include "AWeapon.hpp"

class PowerFist : public AWeapon
{
	public:
		PowerFist();
		PowerFist(const PowerFist& copy);
		PowerFist& operator=(const PowerFist& obj);
		virtual ~PowerFist();

		/* inherit overload function */
		virtual void attack() const;

		/* declare member function */
};

/* global operator overload */

#endif
