#include "DeepCoreMiner.hpp"

DeepCoreMiner::DeepCoreMiner() {}
DeepCoreMiner::~DeepCoreMiner() {}
DeepCoreMiner::DeepCoreMiner(const DeepCoreMiner& copy) { *this = copy; }
DeepCoreMiner& DeepCoreMiner::operator=(const DeepCoreMiner&) { return (*this); }

void
DeepCoreMiner::mine(IAsteroid* obj)
{
	std::cout << "* mining deep... got "
	<< obj->beMined(this) << "! *" << std::endl;
}
