#include "phonebook.hpp"

namespace {
	void print_short(std::string text)
	{
		std::cout << std::setw(9) << text.substr(0, 9);
		std::cout << ".";
	}

	int	get_idx(void)
	{
		std::string		idx;

		do
		{
			print::message("Enter the indexes you want to look up in more detail.");
			std::cout << ": ";
			if (!std::getline(std::cin, idx))
				throw (CTRL_D_ERR);
		} while (idx.empty() || idx.size() != 1 || idx[0] < '0' \
		|| idx.at(0) > Contact::get_contact_count() + '0' - 1);
		return (idx.at(0) - 48);
	}

	void show_detail(Contact &data)
	{
		std::cout << std::endl;
		for (int i = 0; i < 11; i++)
			std::cout << Form::get_field(i) << " : " << data.get_data(i) << std::endl;
		std::cout << std::endl;
	}
}

namespace execute {
	void show_contact_list(Contact *contact)
	{
		std::cout << std::endl;
		std::cout << std::setw(10) << "index" << "|";
		std::cout << std::setw(10) << "first name" << "|";
		std::cout << std::setw(10) << "last name" << "|";
		std::cout << std::setw(10) << "nickname" << std::endl;
		std::cout << std::string(43, '-') << std::endl;
		for (int i = 0; i < Contact::get_contact_count(); i++)
		{
			std::cout << std::setw(10) << i;
			std::cout << "|";
			if (contact[i].get_data(0).size() > 10)
				print_short(contact[i].get_data(0));
			else
				std::cout << std::setw(10) << contact[i].get_data(0);
			std::cout << "|";
			if (contact[i].get_data(1).size() > 10)
				print_short(contact[i].get_data(1));
			else
				std::cout << std::setw(10) << contact[i].get_data(1);
			std::cout << "|";
			if (contact[i].get_data(2).size() > 10)
				print_short(contact[i].get_data(2));
			else
				std::cout << std::setw(10) << contact[i].get_data(2);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void	search(Contact *contact)
	{
		int		idx;

		if (Contact::get_contact_count() == 0)
		{
			print::message("There is no saved contact");
			std::cout << std::endl;
			return ;
		}
		execute::show_contact_list(contact);
		idx = get_idx();
		show_detail(contact[idx]);
	}
}
