#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		this->srcs[i] = nullptr;
	this->count = 0;
}

MateriaSource::MateriaSource(const MateriaSource& copy) { *this = copy; }

MateriaSource& MateriaSource::operator=(const MateriaSource& obj)
{
	if (this == &obj)
		return (*this);
	this->~MateriaSource();
	this->count = obj.getCount();
	for (int i = 0; i < this->count; i++)
		this->srcs[i] = obj.srcs[i]->clone();
	return (*this);
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < this->count; i++)
		delete this->srcs[i];
	this->count = 0;
}

int
MateriaSource::getCount(void) const { return this->count; }

void
MateriaSource::learnMateria(AMateria* materia)
{
	if (this->count >= 4)
		return ;
	this->srcs[count] = materia;
	this->count += 1;
}

AMateria*
MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < this->count; i++)
		if (type == this->srcs[i]->getType())
			return (this->srcs[i]->clone());
	return (NULL);
}
