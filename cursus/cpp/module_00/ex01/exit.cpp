#include "phonebook.hpp"

namespace execute {
	int		exit(void)
	{
		std::string		input;

		while (1)
		{
			std::cout << "Your all cantact will be deleted. Are you okay? (y/n)"
					  << std::endl;
			std::getline(std::cin, input);
			if (input == "y")
				return (true);
			else if (input == "n")
				return (false);
		}
		return (true);
	}
}
