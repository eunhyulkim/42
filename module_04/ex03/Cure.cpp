#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {}
Cure::~Cure() { this->_xp = 0; }
Cure::Cure(const Cure& copy) : AMateria(copy) {}
Cure& Cure::operator=(const Cure& obj) {
	 this->AMateria::operator=(obj);
	 return (*this);
}

AMateria* Cure::clone() const { return (new Cure(*this)); }

void
Cure::use(ICharacter& target)
{
	this->AMateria::use(target);
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
