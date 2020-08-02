#include "MiningBarge.hpp"

MiningBarge::MiningBarge()
{
	for (int i = 0; i < 4; i++)
		this->_srcs[i] = nullptr;
	this->_count = 0;
}

MiningBarge::MiningBarge(const MiningBarge& copy) { *this = copy; }

MiningBarge& MiningBarge::operator=(const MiningBarge& obj)
{
	if (this == &obj)
		return (*this);
	this->~MiningBarge();
	this->_count = obj.getCount();
	for (int i = 0; i < this->_count; i++)
		this->_srcs[i] = obj._srcs[i];
	return (*this);
}

MiningBarge::~MiningBarge() { this->_count = 0; }


int
MiningBarge::getCount(void) const { return this->_count; }

void
MiningBarge::equip(IMiningRaser* miner)
{
	int i;

	if (this->_count >= 4)
		return ;
	i = 0;
	while (i <= this->_count)
		if (this->_srcs[i++] == miner)
			return ;
	this->_srcs[this->_count] = miner;
	this->_count += 1;
}

void
MiningBarge::mine(IAsteroid* obj) const
{
	int i;

	i = 0;
	while (i < this->_count)
		this->_srcs[i++]->mine(obj);
}
