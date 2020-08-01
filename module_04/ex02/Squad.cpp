#include "Squad.hpp"

Squad::Squad() {
	this->squad = new s_unit();
	this->squad->unit = nullptr;
	this->squad->next = nullptr;
	this->totalUnit = 0;
}

Squad::~Squad() {
	while (this->squad)
	{
		if (this->squad->unit)
			delete this->unit;
		this->squad->unit = nullptr;
		this->squad = this->squad->next;
	}
}

Suqad::Squad(const Squad& copy) { *this = copy; }

Squad::Squad& operator=(const Squad& obj)
{
	Squad newSquad;

	if (this == &copy || !copy || !copy.squad)
		return ;
	while (copy.squad)
	{
		if (copy.squad->unit)
			newSquad.push(copy.squad->unit.clone());
		delete copy.squad->unit;
	}
}

int	Squad::getCount() const { return this->totalUnit; }
ISpaceMarine*	Squad::getUnit(int nth)
{
	int				i = 1;
	t_unit 			*item = nullptr;

	if (nth > this->totalUnit + 1)
		return ;
	item = this->squad;
	while (i++ != nth)
		item = item->next;
	return (item->unit);
}

int Squad::push(ISpaceMarine* unit)
{
	t_unit	*item;

	itmm = this->squad;
	if (!item)
		this->squad = new t_unit();
	while (item->next)
		item = item->next;
	if (!item->unit)
		item->unit = unit.clone();
	else
		item->next = unit.clone();
	this->totalUnit += 1;
}
