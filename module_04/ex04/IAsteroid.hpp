#ifndef I_ASTEROID_HPP
# define I_ASTEROID_HPP

# include <string>

class DeepCoreMiner;
class StripMiner;

class IAsteroid
{
	public:
		virtual ~IAsteroid() {}
		virtual std::string beMined(DeepCoreMiner *raser) const = 0;
		virtual std::string beMined(StripMiner *raser) const = 0;
		virtual std::string get_m_name() const = 0;
};

#endif
