#ifndef MINING_BARGE_HPP
# define MINING_BARGE_HPP

#include "IMiningRaser.hpp"
#include "IAsteroid.hpp"

class MiningBarge
{
	private:
		IMiningRaser	*_srcs[4];
		int				_count;

	public:
		MiningBarge();
		MiningBarge(const MiningBarge& copy);
		MiningBarge& operator=(const MiningBarge& obj);
		~MiningBarge();
		void equip(IMiningRaser* miner);
		int getCount(void) const;
		void mine(IAsteroid* obj) const;
};

#endif
