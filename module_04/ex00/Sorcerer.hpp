#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <iostream>
# include <string>
# include "Victim.hpp"
# include "Peon.hpp"

class Victim;
class Peon;

class Sorcerer {
	private:
		std::string		name;
		std::string		title;
		Sorcerer();
	public:
		Sorcerer(std::string name, std::string title);
		Sorcerer& operator=(const Sorcerer& obj);
		Sorcerer(const Sorcerer& copy);
		~Sorcerer();

		std::string getName(void) const;
		std::string getTitle(void) const;
		void polymorph(Victim const &victim) const;
		void polymorph(Peon const &peon) const;
};

std::ostream& operator<<(std::ostream& os, const Sorcerer& s);
#endif
