#include "Squad.hpp"

void
Squad::init(Squad *obj)
{
	obj->squad = new t_squad();
	obj->squad->unit = nullptr;
	obj->squad->next = nullptr;
	obj->totalUnit = 0;
}

void
Squad::deepCopy(const Squad& copy)
{
	t_squad *item;
	ISpaceMarine *t;

	item = copy.squad;
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

Squad::Squad() {
	this->init(this);
}

Squad::~Squad() {
	t_squad 	*temp;

	while (this->squad)
	{
		if (this->squad->unit)
			delete this->squad->unit;
		this->squad->unit = nullptr;
		temp = this->squad;
		this->squad = this->squad->next;
		delete temp;
	}
	this->squad = nullptr;
	this->totalUnit = 0;
}

Squad::Squad(const Squad& copy) {
	if (&copy == nullptr)
		return ;
	this->init(this);
	this->deepCopy(copy);
}

Squad& Squad::operator=(const Squad& obj)
{
	if (&obj == nullptr || &obj == this)
		return (*this);

	this->~Squad();
	this->init(this);
	this->deepCopy(obj);
	return (*this);
}

int	Squad::getCount() const { return this->totalUnit; }
ISpaceMarine*	Squad::getUnit(int nth) const
{
	int				i;
	t_squad 		*item;

	i = 0;
	item = nullptr;
	if (nth > this->totalUnit - 1 || nth < 0)
		return (NULL);
	item = this->squad;
	while (i++ < nth)
		item = item->next;
	return (item->unit);
}

int Squad::push(ISpaceMarine* unit)
{
	t_squad	*item;

	if (!this->squad)
		this->squad = new t_squad();
	item = this->squad;
	while (item->next)
		item = item->next;
	if (!item->unit)
		item->unit = unit;
	else
	{
		item->next = new t_squad();
		item->next->unit = unit;
	}
	this->totalUnit += 1;
	return (this->totalUnit);
}
