#ifndef DEEP_CORE_MINER_HPP
# define DEEP_CORE_MINER_HPP

# include <string>
# include <iostream>

# include "IAsteroid.hpp"
# include "IMiningRaser.hpp"

class DeepCoreMiner : public IMiningRaser
{
	private:
	public:
		DeepCoreMiner();
		DeepCoreMiner(const DeepCoreMiner&);
		DeepCoreMiner& operator=(const DeepCoreMiner& obj);
		virtual ~DeepCoreMiner();

		/* inherit overload function */
		virtual void mine(IAsteroid* obj);
};

#endif
