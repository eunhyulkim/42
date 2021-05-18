#ifndef STRIP_MINER_HPP
# define STRIP_MINER_HPP

# include <iostream>

# include "IAsteroid.hpp"
# include "IMiningRaser.hpp"

class StripMiner : public IMiningRaser
{
	private:
	public:
		StripMiner();
		StripMiner(const StripMiner&);
		StripMiner& operator=(const StripMiner& obj);
		virtual ~StripMiner();

		/* inherit overload function */
		virtual void mine(IAsteroid* obj);
};

#endif
