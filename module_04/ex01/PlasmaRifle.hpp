#ifndef PLASMA_RIFLE_HPP
# define PLASMA_RIFLE_HPP

# include <string>
# include "AWeapon.hpp"

class PlasmaRifle : public AWeapon
{
	public:
		PlasmaRifle();
		PlasmaRifle& operator=(const PlasmaRifle& obj);
		PlasmaRifle(const PlasmaRifle& copy);
		~PlasmaRifle();

		void attack(void) const;
};

#endif
