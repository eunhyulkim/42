#ifndef AWEAPON_HPP
# define AWEAPON_HPP

# include <string>
# include <iostream>

class AWeapon
{
	protected:
		AWeapon();
		std::string name;
		int apcost;
		int damage;
	public:
		AWeapon(std::string const & name, int apcost, int damage);
		AWeapon& operator=(const AWeapon& obj);
		AWeapon(const AWeapon& copy);
		~AWeapon();
		std::string getName(void) const;
		int getAPCost() const;
		int getDamage() const;
		virtual void attack() const = 0;
};

#endif
