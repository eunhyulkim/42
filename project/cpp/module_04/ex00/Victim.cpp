#include "Victim.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Victim::Victim() {}
Victim::Victim(const std::string& name)
: m_name(name)
{
	std::cout << "Some random victim called ";
	std::cout << this->m_name;
	std::cout << " just appeared!" << std::endl;
}

Victim::Victim(const Victim& copy)
: m_name(copy.get_m_name())
{
	std::cout << "Some random victim called ";
	std::cout << this->m_name;
	std::cout << " just appeared!" << std::endl;	
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Victim::~Victim()
{
	std::cout << "Victim ";
	std::cout << this->get_m_name();
	std::cout << " just died for no apparent reason!" << std::endl;
	this->m_name.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Victim& Victim::operator=(const Victim& obj)
{
	if (this == &obj)
		return (*this);
	this->m_name = obj.get_m_name();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Victim& victim)
{
	out << "I'm " << victim.get_m_name();
	out << " and I like otters!" << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Victim::get_m_name() const { return (this->m_name); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Victim::getPolymorphed(void) const {
	std::cout << this->get_m_name();
	std::cout << " has been turned into a cute little sheep!" << std::endl;
}
