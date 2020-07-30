#include "Peon.hpp"

Peon::Peon(std::string name) : Victim(name) {
	std::cout << "Zog zog." << std::endl;
}

Peon&
Peon::operator=(const Peon& obj) {
	this->Victim::operator=(obj);
	return (*this);
}

Peon::Peon(const Peon& copy) : Victim(copy) {
	*this = copy;
	std::cout << "Zog zog." << std::endl;
}

Peon::~Peon() {
	std::cout << "Bleuark..." << std::endl;
}

void
Peon::getPolymorphed(void) const {
	std::cout << this->name
	<< " has been turned into a pink pony!" << std::endl;
};

std::ostream&
operator<<(std::ostream& os, const Peon& p) {
  os << "I'm " << p.getName()
  << " and I like otters!" << std::endl;
  return os;
}
