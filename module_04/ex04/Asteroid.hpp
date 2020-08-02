#ifndef ASTEROID_HPP
# define ASTEROID_HPP

#include "IAsteroid.hpp"

class StripMiner;
class DeepCoreMiner;

class Asteroid : public IAsteroid
{
	private:
		std::string name;
	public:
		Asteroid(std::string name = "Asteroid");
		Asteroid(const Asteroid& copy);
		Asteroid& operator=(const Asteroid& obj);
		~Asteroid();
		std::string beMined(DeepCoreMiner *raser) const;
		std::string beMined(StripMiner *raser) const;
		std::string getName() const;
};

#endif
