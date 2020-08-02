#ifndef STRIP_MINER_HPP
# define STRIP_MINER_HPP

#include "IMiningRaser.hpp"
#include <iostream>

class StripMiner : public IMiningRaser
{
	public:
		StripMiner();
		~StripMiner();
		StripMiner(const StripMiner& copy);
		StripMiner& operator=(const StripMiner& obj);
		void mine(IAsteroid* obj);
};

#endif
