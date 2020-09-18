#include "Config.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Config::Config() {}
Config::Config(/* constructor parameter */)
: /* constructor initialize list */
{
	/* constructor code */
}

Config::Config(const Config& copy)
: /* copy-constructor initialize list */
{
	/* copy-constructor code */
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Config::~Config()
{
	/* destructor code */
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Config& Config::operator=(const Config& obj)
{
	if (this == &obj)
		return (*this);
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Config& config)
{
	/* ostream output overload code */
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
