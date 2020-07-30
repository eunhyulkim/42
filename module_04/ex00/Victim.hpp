#ifndef VICTIM_HPP
# define VICTIM_HPP

# include <iostream>
# include <string>

class Victim {
	protected:
		Victim();
		std::string		name;
	public:
		Victim(std::string name);
		Victim& operator=(const Victim& obj);
		Victim(const Victim& copy);
		~Victim();

		std::string getName(void) const;
		void getPolymorphed(void) const;
};

std::ostream& operator<<(std::ostream& os, const Victim& p);
#endif
