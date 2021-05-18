#include "Squad.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Squad::Squad() {
	this->init(this);
}

Squad::Squad(const Squad& copy)
{
	this->init(this);
	this->deepCopy(copy);
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Squad::~Squad()
{
	t_squad 	*temp;

	while (this->m_squad)
	{
		if (this->m_squad->unit)
			delete this->m_squad->unit;
		this->m_squad->unit = nullptr;
		temp = this->m_squad;
		this->m_squad = this->m_squad->next;
		delete temp;
	}
	this->m_squad = nullptr;
	this->m_total_unit = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Squad& Squad::operator=(const Squad& obj)
{
	if (this == &obj)
		return (*this);
	this->~Squad();
	this->init(this);
	this->deepCopy(obj);
	return (*this);
}

int
Squad::getCount() const {
	return (this->m_total_unit);
}

ISpaceMarine*
Squad::getUnit(int nth) const
{
	int			i;
	t_squad 	*item;

	i = 0;
	if (nth > this->m_total_unit - 1 || nth < 0)
		return (nullptr);
	item = this->m_squad;
	while (i++ < nth)
		item = item->next;
	return (item->unit);
}

int
Squad::push(ISpaceMarine* unit)
{
	t_squad	*item;

	if (!unit)
		return (this->m_total_unit);
	if (!this->m_squad)
	{
		this->m_squad = new t_squad();
		this->m_squad->unit = nullptr;
		this->m_squad->next = nullptr;
	}
	item = this->m_squad;
	while (item->next)
	{
		if (item->unit == unit || item->next->unit == unit)
			return (this->m_total_unit);
		item = item->next;
	}
	if (!item->unit)
		item->unit = unit;
	else
	{
		item->next = new t_squad();
		item->next->unit = unit;
		item->next->next = nullptr;
	}
	this->m_total_unit += 1;
	return (this->m_total_unit);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

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
Squad::init(Squad *obj) {
	obj->m_squad = new t_squad();
	obj->m_squad->unit = nullptr;
	obj->m_squad->next = nullptr;
	obj->m_total_unit = 0;
}

void
Squad::deepCopy(const Squad& copy)
{
	t_squad *item;
	ISpaceMarine *t;

	item = copy.m_squad;
	while (item)
	{
		if (item->unit)
		{
			t = item->unit->clone();
			this->push(t);
		}
		item = item->next;
	}
}
