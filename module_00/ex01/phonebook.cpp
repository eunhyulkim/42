#include "phonebook.hpp"
#include <signal.h>

namespace {
	enum Cmd
	{
		CMD_NONE,
		CMD_ADD,
		CMD_SEARCH,
		CMD_EXIT,
		CMD_FAIL
	};
}

namespace {
	void	show_commands(void)
	{
		std::cout << "# Input your command." << std::endl;
		std::cout << "- ADD, SEARCH, EXIT" << std::endl;
		std::cout << std::endl;
	}
}

namespace {
	Cmd	get_command(void)
	{
		std::string		input;

		std::cout << ": ";
		if (!std::getline(std::cin, input))
			return (CMD_FAIL);
		if (input == "ADD")
			return (CMD_ADD);
		else if (input == "SEARCH")
			return (CMD_SEARCH);
		else if (input == "EXIT")
			return (CMD_EXIT);
		return (CMD_NONE);
	}
}

int		main(void)
{
	Cmd		cmd = CMD_NONE;
	Contact	contact[8];

	print::login_art();
	while (1)
	{
		try
		{
			show_commands();
			cmd = get_command();
			if (cmd == CMD_SEARCH)
				execute::search(contact);
			else if (cmd == CMD_ADD)
				execute::add(contact);
			else if (cmd == CMD_FAIL || (cmd == CMD_EXIT && execute::exit()))
				break ;
			else
				print::not_valid_cmd();
		}
		catch (char const *msg)
		{
			print::message(msg);
			break ;
		}
	}
	return (0);
}
