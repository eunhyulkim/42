#ifndef COMET_HPP
# define COMET_HPP

# include <string>
# include <iostream>

# include "IAsteroid.hpp"

class DeepCoreMiner;
class StripMiner;

class Comet : public IAsteroid
{
	private:
		const std::string m_name;
	public:
		Comet();
		Comet(const Comet& copy);
		Comet& operator=(const Comet& obj);
		virtual ~Comet();

		/* inherit overload function */
		virtual std::string beMined(DeepCoreMiner *) const;
		virtual std::string beMined(StripMiner *) const;
		virtual std::string get_m_name() const;
};

#endif
