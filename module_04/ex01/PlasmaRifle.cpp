#include "PlasmaRifle.hpp"

PlasmaRifle::PlasmaRifle()
: AWeapon("PlasmaRifle", 5, 21) {}
PlasmaRifle::~PlasmaRifle() {}

PlasmaRifle&
PlasmaRifle::operator=(const PlasmaRifle& obj) {
	this->AWeapon::operator=(obj);
	std::cout << "[WEST-ASSIGN] PlasmaRifle" << std::endl;
	return (*this);
}

PlasmaRifle::PlasmaRifle(const PlasmaRifle& copy)
: AWeapon(copy) {
	std::cout << "[WEST-COPY] PlasmaRifle" << std::endl;
}

void
PlasmaRifle::attack(void) const
{
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
}
