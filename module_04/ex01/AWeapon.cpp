#include "AWeapon.hpp"

AWeapon::AWeapon(){}
AWeapon::AWeapon(std::string const & name, int apcost, int damage) \
: name(name), apcost(apcost), damage(damage) {}
AWeapon::~AWeapon() {}

AWeapon&
AWeapon::operator=(const AWeapon& obj) {
	if (this != &obj)
	{
		this->name = obj.name;
		this->damage = obj.damage;
		this->apcost = obj.apcost;
	}
	return (*this);
}

AWeapon::AWeapon(const AWeapon& copy) {
	*this = copy;
}

std::string AWeapon::getName(void) const { return (this->name); }
int AWeapon::getAPCost(void) const { return (this->apcost); }
int AWeapon::getDamage(void) const { return (this->damage); }
