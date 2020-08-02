#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include <iostream>
# include "AWeapon.hpp"
# include "Enemy.hpp"

class Character
{
	protected:
		Character();
		Character& operator=(const Character&);
		Character(const Character&);
		std::string name;
		int			ap;
		AWeapon 	*weapon;
	public:
		Character(std::string const & name);
		~Character();

		void recoverAP(void);
		void equip(AWeapon* equipment);
		void attack(Enemy* enemy);
		std::string getName(void) const;
		AWeapon *getWeapon(void) const;
		int getAP(void) const;
};

std::ostream& operator<<(std::ostream& os, const Character& s);

#endif
