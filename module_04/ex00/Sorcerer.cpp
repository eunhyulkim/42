#include "Sorcerer.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Sorcerer::Sorcerer() {}
Sorcerer::Sorcerer(const std::string& name, const std::string& title)
: m_name(name), m_title(title)
{
	std::cout << this->get_m_name();
	std::cout << ", " << this->get_m_title();
	std::cout << ", is born!" << std::endl;
}

Sorcerer::Sorcerer(const Sorcerer& copy)
: m_name(copy.get_m_name()), m_title(copy.get_m_title())
{
	std::cout << this->get_m_name();
	std::cout << ", " << this->get_m_title();
	std::cout << ", is born!" << std::endl;	
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Sorcerer::~Sorcerer()
{
	std::cout << this->get_m_name();
	std::cout << ", " << this->get_m_title();
	std::cout << ", is dead. Consequences will never be the same!";
	std::cout << std::endl;
	this->m_name.clear();
	this->m_title.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Sorcerer&
Sorcerer::operator=(const Sorcerer& obj)
{
	if (this == &obj)
		return (*this);
	this->m_name = obj.get_m_name();
	this->m_title = obj.get_m_title();
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Sorcerer& sorcerer)
{
	out << "I am " << sorcerer.get_m_name();
	out << ", " << sorcerer.get_m_title();
	out << ", and I like ponies!" << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Sorcerer::get_m_name() const { return (this->m_name); }
std::string Sorcerer::get_m_title() const { return (this->m_title); }

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
Sorcerer::polymorph(Victim const &victim) const {
	victim.getPolymorphed();
}
