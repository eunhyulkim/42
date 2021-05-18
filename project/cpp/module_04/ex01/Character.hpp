#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include <iostream>

# include "AWeapon.hpp"
# include "Enemy.hpp"

class Character
{
	private:
		std::string m_name;
		int m_ap;
		AWeapon *m_weapon;
		Character& operator=(const Character&);
		Character(const Character&);
	protected:
		Character();
	public:
		Character(const std::string& name);
		virtual ~Character();

		/* getter function */
		std::string get_m_name() const;
		int get_m_ap() const;
		AWeapon *get_m_weapon() const;

		/* declare member function */
		void recoverAP(void);
		void equip(AWeapon* equipment);
		void attack(Enemy* enemy);
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Character& character);

#endif
