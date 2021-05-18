#include "Character.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Character::Character() {}
Character::Character(const std::string name) : m_name(name), m_count(0)
{
	for (int i = 0; i < 4; i++)
		this->m_srcs[i] = nullptr;
}

Character::Character(const Character& copy)
: m_name(copy.get_m_name()), m_count(copy.get_m_count())
{
	for (int i = 0; i < this->m_count; i++)
	{
		if (copy.getMateria(i) != nullptr)
			this->m_srcs[i] = copy.getMateria(i)->clone();
	}
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Character::~Character()
{
	for (int i = 0; i < this->m_count; i++)
	{
		if (this->m_srcs[i] != nullptr)
			delete this->m_srcs[i];
	}
	m_count = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Character& Character::operator=(const Character& obj)
{
	if (this == &obj)
		return (*this);
	this->~Character();
	this->m_count = obj.get_m_count();
	for (int i = 0; i < this->m_count; i++)
	{
		if (obj.getMateria(i) != nullptr)
			this->m_srcs[i] = obj.getMateria(i)->clone();
	}
	return (*this);
}

void
Character::equip(AMateria* m)
{
	if (this->m_count >= 4 || m == nullptr)
		return ;
	for (int i = 0; i < this->m_count; i++)
		if (m == this->m_srcs[i])
			return ;
	this->m_srcs[this->m_count] = m;
	this->m_count += 1;
	return ;
}

void
Character::unequip(int idx)
{
	if (idx < 0 || idx > this->m_count - 1)
		return ;
	while (++idx < this->m_count)
		this->m_srcs[idx - 1] = this->m_srcs[idx];
	this->m_srcs[this->m_count - 1] = nullptr;
	this->m_count--;
	return ;
}

void
Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx > this->m_count - 1)
		return ;
	if (m_srcs[idx] == nullptr)
		return ;
	this->m_srcs[idx]->use(target);
	return ;
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const std::string& Character::get_m_name() const { return (this->m_name); }
int Character::get_m_count() const { return (this->m_count); }

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


AMateria*
Character::getMateria(int idx) const {
	return (this->m_srcs[idx]);
}
