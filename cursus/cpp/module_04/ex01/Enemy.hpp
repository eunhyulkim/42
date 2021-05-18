#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <string>
# include <iostream>

class Enemy
{
	protected:
		std::string m_type;
		int m_hp;
	public:
		Enemy();
		Enemy(int hp, const std::string& type);
		Enemy(const Enemy& copy);
		Enemy& operator=(const Enemy& obj);
		virtual ~Enemy();

		/* getter function */
		std::string get_m_type() const;
		int get_m_hp() const;

		/* declare member function */
		virtual void takeDamage(int damage);
};

/* global operator overload */

#endif
