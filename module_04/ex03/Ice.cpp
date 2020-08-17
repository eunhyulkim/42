#include "Ice.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& copy)
: AMateria(copy) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Ice::~Ice() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Ice& Ice::operator=(const Ice& obj)
{
	if (this == &obj)
		return (*this);
	this->AMateria::operator=(obj);
	return (*this);
}

AMateria* Ice::clone() const { return (new Ice(*this)); }

void
Ice::use(ICharacter& target) {
	this->AMateria::use(target);
	std::cout << "* shoots an ice bolt at " << target.get_m_name() << std::endl;
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

