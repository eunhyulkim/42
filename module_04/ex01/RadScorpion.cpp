#include "RadScorpion.hpp"

RadScorpion::RadScorpion() : Enemy(80, "RadScorpion") {
	std::cout << "* click click click *" << std::endl;
}
RadScorpion::~RadScorpion() {
	std::cout << "* SPROTCH *" << std::endl;
}

RadScorpion&
RadScorpion::operator=(const RadScorpion& obj) {
	this->Enemy::operator=(obj);
	return (*this);
}

RadScorpion::RadScorpion(const RadScorpion& copy) : Enemy(copy) {
	std::cout << "* click click click *" << std::endl;
}
