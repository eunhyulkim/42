#include <string>
#include <iostream>
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "Enemy.hpp"

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}

	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int		main(void)
{
	PlasmaRifle rifle;
	print("PlasmaRifle Status");
	std::cout << "NAME: " << rifle.getName() << std::endl;
	std::cout << "DAMAGE: " << rifle.getDamage() << std::endl;
	std::cout << "APCOST: " << rifle.getAPCost() << std::endl;
	print("PlasmaRifle Attack Test");
	rifle.attack();

	PowerFist fist;
	print("PowerFist Status");
	std::cout << "NAME: " << fist.getName() << std::endl;
	std::cout << "DAMAGE: " << fist.getDamage() << std::endl;
	std::cout << "APCOST: " << fist.getAPCost() << std::endl;
	print("PowerFist Attack Test");
	fist.attack();

	Enemy enemy(100, "Demon");
	print("Basic Enemy Status");
	std::cout << "TYPE: " << enemy.getType() << std::endl;
	std::cout << "HP: " << enemy.getHP() << std::endl;

	print("Basic Take Damage Test");
	enemy.takeDamage(30);
	std::cout << "AFTER HP: " << enemy.getHP() << std::endl;

	print("Overflow Take Damage Test");
	enemy.takeDamage(80);
	std::cout << "AFTER HP: " << enemy.getHP() << std::endl;
	print("TEST END");
	return (0);
}
