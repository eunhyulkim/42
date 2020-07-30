#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <string>
# include <iostream>

class Enemy
{
	protected:
		Enemy();
		std::string type;
		int hp;
	public:
		Enemy(int hp, std::string const & type);
		Enemy& operator=(const Enemy& obj);
		Enemy(const Enemy& copy);
		~Enemy();

		int getHP(void) const;
		std::string getType(void) const;
		virtual void takeDamage(int damage);
};

#endif
