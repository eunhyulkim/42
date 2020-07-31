#include "PowerFist.hpp"

PowerFist::PowerFist()
: AWeapon("PowerFist", 8, 50) {}
PowerFist::~PowerFist() {}

PowerFist&
PowerFist::operator=(const PowerFist& obj) {
	this->AWeapon::operator=(obj);
	std::cout << "[WEST-ASSIGN] PowerFist" << std::endl;
	return (*this);
}

PowerFist::PowerFist(const PowerFist& copy)
: AWeapon(copy) {
	std::cout << "[WEST-COPY] PowerFist" << std::endl;
}

void
PowerFist::attack(void) const {
	std::cout << "* pschhh... SBAM! *" << std::endl;
}
