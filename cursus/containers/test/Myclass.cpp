#include "Myclass.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Myclass::Myclass() {}
Myclass::Myclass(const std::string& name)
: m_name(name) {}

Myclass::Myclass(const Myclass& copy)
: m_name(copy.m_name) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Myclass::~Myclass(){}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Myclass& Myclass::operator=(const Myclass& obj)
{
	if (this == &obj)
		return (*this);
	this->m_name = obj.m_name;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Myclass& myclass) {
	out << myclass.get_m_name();
	return (out);
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

const std::string&
Myclass::get_m_name() const { return (this->m_name); }

std::string&
Myclass::operator*() { return (this->m_name); }

const std::string&
Myclass::operator*() const { return (this->m_name); }

bool
Myclass::operator!=(const Myclass& obj) const { return (this->m_name != obj.m_name); }

bool
Myclass::operator==(const Myclass& obj) const { return (this->m_name == obj.m_name); }

bool
Myclass::operator<(const Myclass& obj) const { return (this->m_name < obj.m_name); }

bool
Myclass::operator<=(const Myclass& obj) const { return (this->m_name <= obj.m_name); }

bool
Myclass::operator>(const Myclass& obj) const { return (this->m_name > obj.m_name); }

bool
Myclass::operator>=(const Myclass& obj) const { return (this->m_name >= obj.m_name); }
