#ifndef MINING_BARGE_HPP
# define MINING_BARGE_HPP

# include <string>
# include <iostream>

#include "IMiningRaser.hpp"
#include "IAsteroid.hpp"

class MiningBarge
{
	private:
		IMiningRaser *m_srcs[4];
		int m_count;
	public:
		MiningBarge();
		MiningBarge(const MiningBarge& copy);
		MiningBarge& operator=(const MiningBarge& obj);
		virtual ~MiningBarge();

		/* getter function */
		int get_m_count() const;

		/* declare member function */
		void equip(IMiningRaser* miner);
		void mine(IAsteroid* obj) const;
};

#endif
