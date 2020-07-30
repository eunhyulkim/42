#include "Victim.hpp"

Victim::Victim(std::string name) : name(name) {
	std::cout << "Some random victim called " << this->name
	<< " just appeared!" << std::endl;
}

Victim::Victim() {}

Victim&
Victim::operator=(const Victim& obj) {
	if (this != &obj)
		this->name = obj.name;
	return (*this);
}

Victim::Victim(const Victim& copy) {
	*this = copy;
	std::cout << "Some random victim called " << this->name
	<< " just appeared!" << std::endl;
}

Victim::~Victim() {
	std::cout << "Victim " << this->name
	<< " just died for no apparent reason!" << std::endl;
}

std::string
Victim::getName(void) const {
	return (this->name);
}

void
Victim::getPolymorphed(void) const {
	std::cout << this->name
	<< " has been turned into a cute little sheep!" << std::endl;
};

std::ostream&
operator<<(std::ostream& os, const Victim& p) {
  os << "I'm " << p.getName()
  << " and I like otters!" << std::endl;
  return os;
}
