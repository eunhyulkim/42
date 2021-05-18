#ifndef I_MINING_RASER_HPP
# define I_MINING_RASER_HPP

#include "IAsteroid.hpp"

class IMiningRaser
{
	public:
		virtual ~IMiningRaser() {}
		virtual void mine(IAsteroid*) = 0;
};

#endif
