#include "AssaultTerminator.hpp"

AssaultTerminator::AssaultTerminator() {
	std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::AssaultTerminator(const AssaultTerminator& copy) {
	*this = copy;
}

AssaultTerminator& AssaultTerminator::operator=(const AssaultTerminator& obj)
{
	if (this == &obj)
		return (*this);
	return (*this);
}

AssaultTerminator::~AssaultTerminator() {
	std::cout << "I’ll be back..." << std::endl;
}

void AssaultTerminator::battleCry(void) const {
	std::cout << "This code is unclean. PURIFY IT!" << std::endl;
}

void AssaultTerminator::rangedAttack(void) const {
	std::cout << "* does nothing *" << std::endl;
}

void AssaultTerminator::meleeAttack(void) const {
	std::cout << "* attacks with chainfists *" << std::endl;
}

ISpaceMarine* AssaultTerminator::clone(void) const {
	return (new AssaultTerminator(*this));
}
