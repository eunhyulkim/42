#include "SuperMutant.hpp"

SuperMutant::SuperMutant() : Enemy(170, "Super Mutant") {
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
}
SuperMutant::~SuperMutant() {
	std::cout << "Aaargh..." << std::endl;
}

SuperMutant&
SuperMutant::operator=(const SuperMutant& obj) {
	this->Enemy::operator=(obj);
	return (*this);
}

SuperMutant::SuperMutant(const SuperMutant& copy) : Enemy(copy) {
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
}

void SuperMutant::takeDamage(int damage) {
	damage -= 3;
	if (damage > hp)
		damage = hp;
	std::cout << "take " << damage
	<< " damage, remain hp is " << (hp - damage) << std::endl;
	hp -= damage;
}
