#include "phonebook.hpp"

namespace print {
	void	login_art(void)
	{
		std::ifstream in(ASCIIART_PATH);
		std::string s;

		if (in.is_open())
		{
			std::getline(in, s, (char)in.eof());
			std::cout << s;
		}
		return ;
	}

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
