#ifndef PEON_HPP
# define PEON_HPP

# include <iostream>
# include <string>
# include "Victim.hpp"

class Victim;

class Peon : public Victim {
	private:
		Peon();
	public:
		Peon(std::string name);
		Peon& operator=(const Peon& obj);
		Peon(const Peon& copy);
		~Peon();

		void getPolymorphed(void) const;
};

std::ostream& operator<<(std::ostream& os, const Peon& p);

#endif
