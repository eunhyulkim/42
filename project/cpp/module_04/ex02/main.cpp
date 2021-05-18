#include "TacticalMarine.hpp"
#include "AssaultTerminator.hpp"
#include "Squad.hpp"

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int custom_main()
{
	print("CREATE UNIT");
	ISpaceMarine* bob = new TacticalMarine;
	ISpaceMarine* jim = new AssaultTerminator;
	ISpaceMarine* son = new AssaultTerminator;

	print("LEAK CHECK");
	std::cout << bob << std::endl;
	std::cout << jim << std::endl;
	std::cout << son << std::endl;
	print("CREATE SQUAD");
	Squad* vlc = new Squad;
	vlc->push(bob);
	vlc->push(jim);
	vlc->push(bob);
	vlc->push(nullptr);

	print("GET UNIT CHECK");
	std::cout << vlc->getUnit(0) << std::endl;
	std::cout << vlc->getUnit(1) << std::endl;
	std::cout << vlc->getUnit(2) << std::endl;
	std::cout << vlc->getUnit(3) << std::endl;
	print("CHECK UNIT COUNT(2)");
	std::cout << vlc->getCount() << std::endl;
	print("EXCUCTE COPY CONSTRUCTOR");
	Squad* nvlc = new Squad(*vlc);
	print("CHECK DEEP COPY");
	std::cout << nvlc->getUnit(0) << std::endl;
	std::cout << nvlc->getUnit(1) << std::endl;
	std::cout << nvlc->getUnit(2) << std::endl;
	std::cout << nvlc->getUnit(3) << std::endl;
	print("CHECK UNIT COUNT(2)");
	std::cout << nvlc->getCount() << std::endl;
	print("ASSIGN SQUAD WITH ADDED UNIT");
	vlc->push(son);
	*nvlc = *vlc;
	std::cout << nvlc->getUnit(0) << std::endl;
	std::cout << nvlc->getUnit(1) << std::endl;
	std::cout << nvlc->getUnit(2) << std::endl;
	std::cout << nvlc->getUnit(3) << std::endl;
	print("CHECK UNIT COUNT(3)");
	std::cout << nvlc->getCount() << std::endl;
	print("TEST END, DESTRUCTOR WILL CALL");
	delete vlc;
	delete nvlc;

	return 0;
}

int main()
{
	print("BASIC TEST");
	ISpaceMarine* bob = new TacticalMarine;
	ISpaceMarine* jim = new AssaultTerminator;
	ISquad* vlc = new Squad;
	vlc->push(bob);
	vlc->push(jim);
	for (int i = 0; i < vlc->getCount(); ++i)
	{
		ISpaceMarine* cur = vlc->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}
	delete vlc;
	custom_main();
	return 0;
}
