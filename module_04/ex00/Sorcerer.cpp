#include "Sorcerer.hpp"

Sorcerer::Sorcerer(std::string name, std::string title)
: name(name), title(title) {
	std::cout << this->name << ", "
	<< this->title << ", is born!" << std::endl;
}

Sorcerer&
Sorcerer::operator=(const Sorcerer& obj) {
	if (this != &obj)
	{
		this->name = obj.name;
		this->title = obj.title;
	}
	return (*this);
}

Sorcerer::Sorcerer(const Sorcerer& copy) {
	*this = copy;
}

Sorcerer::~Sorcerer() {
	std::cout << this->name << ", "
	<< this->title << ", is dead. "
	<< "Consequences will never be the same!"
	<< std::endl;
}

void
Sorcerer::introduce(void) {
	std::cout << "I am " << this->name << ", "
	<< this->title << ", and I like ponies!" << std::endl;
}
