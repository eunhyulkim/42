#include "PresidentalPardonForm.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

PresidentalPardonForm::PresidentalPardonForm() {}
PresidentalPardonForm::PresidentalPardonForm(/* constructor parameter */)
: /* constructor initialize list */
{
	/* constructor code */
}

PresidentalPardonForm::PresidentalPardonForm(const PresidentalPardonForm& copy)
: /* copy-constructor initialize list */
{
	/* copy-constructor code */
	*this = copy;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

PresidentalPardonForm::~PresidentalPardonForm()
{
	/* destructor code */
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

PresidentalPardonForm& PresidentalPardonForm::operator=(const PresidentalPardonForm& obj)
{
	if (this == &obj)
		return (*this);
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const PresidentalPardonForm& presidentalPardonForm)
{
	out << /* write to what you print(PresidentalPardonForm.member) */ << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* getter code */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
