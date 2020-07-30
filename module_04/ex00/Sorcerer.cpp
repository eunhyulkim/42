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

std::string Sorcerer::getName(void) const { return (this->name); }
std::string Sorcerer::getTitle(void) const { return (this->title); }

void
Sorcerer::polymorph(Victim const &victim) const {
	victim.getPolymorphed();
}

void
Sorcerer::polymorph(Peon const &peon) const {
	peon.getPolymorphed();
}

std::ostream&
operator<<(std::ostream& os, const Sorcerer& s) {
os << "I am " << s.getName() << ", "
<< s.getTitle() << ", and I like ponies!" << std::endl;
  return os;
}
