#include <iostream>
#include "DeepCoreMiner.hpp"
#include "StripMiner.hpp"
#include "Asteroid.hpp"
#include "Comet.hpp"
#include "MiningBarge.hpp"

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	IMiningRaser *raser1 = new DeepCoreMiner();
	IMiningRaser *raser2 = new StripMiner();
	IAsteroid *steroid = new Asteroid();
	IAsteroid *comet = new Comet();

	print("MINE EACH OTHER STEROID WITH TWO KIND MINER");
	raser1->mine(steroid);
	raser2->mine(steroid);
	raser1->mine(comet);
	raser2->mine(comet);

	print("BARGE TEST, EXPECTED SAME RESULT");
	MiningBarge *barge = new MiningBarge();
	barge->equip(raser1);
	barge->equip(raser2);
	barge->mine(steroid);
	barge->mine(comet);

	delete barge;
	delete steroid;
	delete comet;
	delete raser1;
	delete raser2;
	return (0);
}
