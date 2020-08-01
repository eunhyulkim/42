#include <string>
#include <iostream>
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "Enemy.hpp"
#include "SuperMutant.hpp"
#include "RadScorpion.hpp"
#include "Character.hpp"

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

	print("Underflow Take Damage Test");
	enemy.takeDamage(80);
	std::cout << "AFTER HP: " << enemy.getHP() << std::endl;

	print("Enemy Status With Copy Counstructor");
	Enemy copy_enemy(enemy);
	std::cout << "TYPE: " << copy_enemy.getType() << std::endl;
	std::cout << "HP: " << copy_enemy.getHP() << std::endl;

	print("Enemy Status With Assign Operator");
	Enemy assign_enemy(enemy);
	Enemy new_enemy(200, "Angel");
	assign_enemy = new_enemy;
	std::cout << "TYPE: " << assign_enemy.getType() << std::endl;
	std::cout << "HP: " << assign_enemy.getHP() << std::endl;

	print("Super Mutant Test");
	SuperMutant mutant;
	std::cout << "TYPE: " << mutant.getType() << std::endl;
	std::cout << "HP: " << mutant.getHP() << std::endl;
	print("Mutant TakeDamage, Expected 17(Reduce 3)");
	mutant.takeDamage(20);
	print("TEST END");

	print("RadScorpion Test");
	RadScorpion scorpion;
	std::cout << "TYPE: " << scorpion.getType() << std::endl;
	std::cout << "HP: " << scorpion.getHP() << std::endl;
	print("Mutant TakeDamage, Expected 20(Reduce 0)");
	scorpion.takeDamage(20);

	print("CHRACTER TEST WITH COUNSTOCTOR");
	Character e("eunhkim");
	PlasmaRifle shot;
	PowerFist fis;
	print("FIST TADMAGE");
	RadScorpion *kid = new RadScorpion();
	print("OVERLOAD << WITH NO WEAPON");
	std::cout << e;
	e.equip(&shot);
	print("CHRACTER ATTACK");
	e.attack(kid);
	std::cout << e.getName() << "(AP: " << e.getAP() << ")" << std::endl;
	e.attack(kid);
	std::cout << e.getName() << "(AP: " << e.getAP() << ")" << std::endl;
	print("EQUIP CHANGE");
	e.equip(&fis);
	e.attack(kid);
	std::cout << e.getName() << "(AP: " << e.getAP() << ")" << std::endl;
	print("RECOVER AP");
	e.recoverAP();
	std::cout << e.getName() << "(AP: " << e.getAP() << ")" << std::endl;
	print("OVERLOAD << WITH WEAPON");
	std::cout << e;
	print("TEST END");
	return (0);
}
