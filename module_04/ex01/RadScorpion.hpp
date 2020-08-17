#ifndef RAD_SCORPION_HPP
# define RAD_SCORPION_HPP

# include <string>
# include <iostream>

# include "Enemy.hpp"

class RadScorpion : public Enemy
{
	public:
		RadScorpion();
		RadScorpion(const RadScorpion& copy);
		RadScorpion& operator=(const RadScorpion& obj);
		virtual ~RadScorpion();
};

#endif
