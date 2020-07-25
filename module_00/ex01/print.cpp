#include "phonebook.hpp"

namespace print {
	void	message(char const *msg)
	{
		std::cout << msg << std::endl;
	}

	void	message(std::string msg)
	{
		std::cout << msg << std::endl;
	}


	void	not_valid_cmd(void)
	{
		std::cout << "Not valid command. retry please." << std::endl;
	}
}
