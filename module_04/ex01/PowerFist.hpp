#ifndef POWER_FIST_HPP
# define POWER_FIST_HPP

# include <string>
# include "AWeapon.hpp"

class PowerFist : public AWeapon
{
	public:
		PowerFist();
		PowerFist& operator=(const PowerFist& obj);
		PowerFist(const PowerFist& copy);
		~PowerFist();

		void attack(void) const;
};

#endif
