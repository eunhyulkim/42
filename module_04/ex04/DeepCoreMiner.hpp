#ifndef DEEP_CORE_MINER_HPP
# define DEEP_CORE_MINER_HPP

#include "IMiningRaser.hpp"
#include <iostream>

class DeepCoreMiner : public IMiningRaser
{
	public:
		DeepCoreMiner();
		~DeepCoreMiner();
		DeepCoreMiner(const DeepCoreMiner& copy);
		DeepCoreMiner& operator=(const DeepCoreMiner& obj);
		void mine(IAsteroid* obj);
};

#endif
