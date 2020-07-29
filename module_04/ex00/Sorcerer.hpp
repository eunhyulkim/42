#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <iostream>
# include <string>

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
		void introduce(void);
};
#endif
