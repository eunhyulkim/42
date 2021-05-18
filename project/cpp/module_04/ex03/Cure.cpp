#include "Cure.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& copy)
: AMateria(copy) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Cure::~Cure() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Cure& Cure::operator=(const Cure& obj)
{
	if (this == &obj)
		return (*this);
	this->AMateria::operator=(obj);
	return (*this);
}

AMateria*
Cure::clone() const { 
	return (new Cure(*this)); 
}

void
Cure::use(ICharacter& target) {
	this->AMateria::use(target);
	std::cout << "* heals " << target.get_m_name() << "'s wounds *" << std::endl;
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* getter code */

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* setter code */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

