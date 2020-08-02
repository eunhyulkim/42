#include "StripMiner.hpp"
#include <typeinfo>

StripMiner::StripMiner() {}
StripMiner::~StripMiner() {}
StripMiner::StripMiner(const StripMiner& copy) { *this = copy; }
StripMiner& StripMiner::operator=(const StripMiner&) { return (*this); }

void
StripMiner::mine(IAsteroid* obj)
{
	std::cout << "* this strip mining... got "
	<< obj->beMined(dynamic_cast<StripMiner*>(this)) << "! *" << std::endl;
}
