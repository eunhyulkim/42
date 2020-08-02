#ifndef COMET_HPP
# define COMET_HPP

#include "IAsteroid.hpp"

class StripMiner;
class DeepCoreMiner;

class Comet : public IAsteroid
{
	private:
		std::string name;
	public:
		Comet(std::string name = "Comet");
		Comet(const Comet& copy);
		Comet& operator=(const Comet& obj);
		~Comet();
		std::string beMined(DeepCoreMiner *) const;
		std::string beMined(StripMiner *) const;
		std::string getName() const;
};

#endif
