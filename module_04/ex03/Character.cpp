#include "Character.hpp"
#include "AMateria.hpp"

Character::Character(const std::string name) : _name(name), _count(0)
{
	for (int i = 0; i < 4; i++)
		this->_srcs[i] = nullptr;
}

Character::~Character()
{
	for (int i = 0; i < this->_count; i++)
		delete this->_srcs[i];
	_count = 0;
}

Character::Character(const Character& copy) : _name(copy.getName()), _count(copy.getCount())
{
	this->_count = copy.getCount();
	for (int i = 0; i < this->_count; i++)
		this->_srcs[i] = copy.getMateria(i)->clone();
}

Character&
Character::operator=(const Character& obj)
{
	if (this == &obj)
		return (*this);
	this->~Character();
	this->_name = obj.getName();
	this->_count = obj.getCount();
	for (int i = 0; i < this->_count; i++)
		this->_srcs[i] = obj.getMateria(i)->clone();
	return (*this);
}

const std::string& Character::getName() const { return (this->_name); }
int Character::getCount() const { return (this->_count); }
AMateria* Character::getMateria(int idx) const { return (this->_srcs[idx]); };

void
Character::equip(AMateria* m)
{
	if (this->_count >= 4 || m == nullptr)
		return ;
	this->_srcs[this->_count] = m;
	this->_count += 1;
	return ;
};

void
Character::unequip(int idx)
{
	if (idx > this->_count - 1)
		return ;
	while (++idx < this->_count)
		this->_srcs[idx - 1] = this->_srcs[idx];
	this->_srcs[this->_count - 1] = nullptr;
	return ;
};

void
Character::use(int idx, ICharacter& target)
{
	if (idx > this->_count - 1)
		return ;
	if (_srcs[idx] == nullptr)
		return ;
	this->_srcs[idx]->use(target);
	return ;
}
