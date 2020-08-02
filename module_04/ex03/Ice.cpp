#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {}
Ice::~Ice() { this->_xp = 0; }
Ice::Ice(const Ice& copy) : AMateria(copy) {}
Ice& Ice::operator=(const Ice& obj)
{
	 this->AMateria::operator=(obj);
	 return (*this);
}

AMateria* Ice::clone() const { return (new Ice(*this)); }

void
Ice::use(ICharacter& target)
{
	this->AMateria::use(target);
	std::cout << "* shoots an ice bolt at " << target.getName() << std::endl;
}
