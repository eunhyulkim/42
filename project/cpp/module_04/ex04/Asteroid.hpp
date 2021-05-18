#ifndef ASTEROID_HPP
# define ASTEROID_HPP

# include <string>
# include <iostream>

# include "IAsteroid.hpp"

class DeepCoreMiner;
class StripMiner;

class Asteroid : public IAsteroid
{
	private:
		const std::string m_name;
	public:
		Asteroid();
		Asteroid(const Asteroid& copy);
		Asteroid& operator=(const Asteroid& obj);
		virtual ~Asteroid();

		/* inherit overload function */
		virtual std::string beMined(DeepCoreMiner *) const;
		virtual std::string beMined(StripMiner *) const;
		virtual std::string get_m_name() const;
};

#endif
