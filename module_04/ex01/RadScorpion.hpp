#ifndef RAD_SCORPION_HPP
# define RAD_SCORPION_HPP

# include <string>
# include <iostream>
# include "Enemy.hpp"

class RadScorpion : public Enemy
{
	public:
		RadScorpion();
		RadScorpion& operator=(const RadScorpion& obj);
		RadScorpion(const RadScorpion& copy);
		~RadScorpion();
};

#endif
