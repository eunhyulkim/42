#ifndef A_WEAPON_HPP
# define A_WEAPON_HPP

# include <string>
# include <iostream>

class AWeapon
{
	protected:
		std::string m_name;
		int m_apcost;
		int m_damage;
		AWeapon();
	public:
		AWeapon(const std::string& name, int apcost, int damage);
		AWeapon(const AWeapon& copy);
		AWeapon& operator=(const AWeapon& obj);
		virtual ~AWeapon();

		/* getter function */
		std::string get_m_name() const;
		int get_m_apcost() const;
		int get_m_damage() const;

		/* declare member function */
		virtual void attack() const = 0;
};

/* global operator overload */

#endif
