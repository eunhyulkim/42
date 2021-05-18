#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <string>
# include <iostream>

# include "Victim.hpp"

class Sorcerer
{
	private:
		std::string m_name;
		std::string m_title;
		Sorcerer();
	public:
		Sorcerer(const std::string& name, const std::string& title);
		Sorcerer(const Sorcerer& copy);
		Sorcerer& operator=(const Sorcerer& obj);
		virtual ~Sorcerer();

		/* getter function */
		std::string get_m_name() const;
		std::string get_m_title() const;

		/* declare member function */
		void polymorph(Victim const &victim) const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Sorcerer& sorcerer);

#endif
