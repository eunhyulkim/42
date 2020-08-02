#include "AMateria.hpp"

AMateria::AMateria(const std::string& type) : _type(type), _xp(0) {}

AMateria::AMateria(const AMateria& copy) : _type(copy.getType()), _xp(copy.getXP()) {}

AMateria& AMateria::operator=(const AMateria& obj)
{
	if (this == &obj)
		return (*this);
	this->_type = obj.getType();
	this->_xp = obj.getXP();
	return (*this);
}

AMateria::~AMateria() {}

const std::string&
AMateria::getType(void) const { return (this->_type); }

unsigned int
AMateria::getXP(void) const { return (this->_xp); }

void
AMateria::use(ICharacter& target){ this->_xp += 10; (void)target; }
