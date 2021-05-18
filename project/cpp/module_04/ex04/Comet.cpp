#include "Comet.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Comet::Comet() : m_name("Comet") {}

Comet::Comet(const Comet& copy) : m_name(copy.get_m_name()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Comet::~Comet() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Comet& Comet::operator=(const Comet& obj)
{
	if (this == &obj)
		return (*this);
	return (*this);
}

std::string
Comet::beMined(DeepCoreMiner *) const {
	return ("Meium");
}

std::string
Comet::beMined(StripMiner *) const {
	return ("Tartarite");
}

std::string
Comet::get_m_name() const {
	return (this->m_name);
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

