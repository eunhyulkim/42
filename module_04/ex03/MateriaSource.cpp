#include "MateriaSource.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; i++)
		this->m_srcs[i] = nullptr;
	this->m_count = 0;
}

MateriaSource::MateriaSource(const MateriaSource& copy)
{
	this->m_count = copy.get_m_count();
	for (int i = 0; i < this->m_count; i++)
		this->m_srcs[i] = copy.m_srcs[i]->clone();
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < this->m_count; i++)
		delete this->m_srcs[i];
	this->m_count = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

MateriaSource& MateriaSource::operator=(const MateriaSource& obj)
{
	if (this == &obj)
		return (*this);
	this->~MateriaSource();
	this->m_count = obj.get_m_count();
	for (int i = 0; i < this->m_count; i++)
		this->m_srcs[i] = obj.m_srcs[i]->clone();
	return (*this);
}

void
MateriaSource::learnMateria(AMateria* materia)
{
	if (this->m_count >= 4)
		return ;
	this->m_srcs[m_count] = materia;
	this->m_count += 1;
}

AMateria*
MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < this->m_count; i++)
		if (type == this->m_srcs[i]->get_m_type())
			return (this->m_srcs[i]->clone());
	return (nullptr);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

int MateriaSource::get_m_count() const { return (this->m_count); }

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

