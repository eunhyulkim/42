#ifndef PEON_HPP
# define PEON_HPP

# include <string>
# include <iostream>

# include "Victim.hpp"

class Peon : public Victim
{
	private:
		Peon();
	public:
		Peon(const std::string& name);
		Peon(const Peon& copy);
		Peon& operator=(const Peon& obj);
		virtual ~Peon();

		/* inherit overload function */
		virtual void getPolymorphed(void) const;

		/* declare member function */
};

/* global operator overload */

#endif
