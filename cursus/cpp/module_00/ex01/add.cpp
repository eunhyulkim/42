#include "phonebook.hpp"

namespace {
	void	remove_contact(Contact *contact, int remove_idx)
	{
		for (int i = 0; i < 11; i++)
			contact[remove_idx].set_data(i, Contact::get_last_contact(contact).get_data(i));
		Contact::add_contact_count(-1);
	}
}

namespace execute {
	void	add(Contact *contact)
	{
		Form	data;
		std::string idx;

		if (Contact::get_contact_count() == 8)
		{
			execute::show_contact_list(contact);
			print::message("sorry, your phonbook is full");
			print::message("If you want to delete a contact, enter index");
			do
			{
				std::cout << ": ";
				if (!std::getline(std::cin, idx))
					throw (CTRL_D_ERR);
			} while (idx.empty() || idx.size() != 1 || idx[0] < '0' \
			|| idx.at(0) > Contact::get_contact_count() + '0' - 1);
			remove_contact(contact, idx.at(0) - 48);
		}
		for (int i = 0; i < 4; i++)
			data.get_mendatory_field(i);
		data.get_generic_field(4);
		data.get_email_field(5);
		data.get_phonenumber_field(6);
		data.get_birthday_field(7);
		for (int i = 8; i < 11; i++)
			data.get_generic_field(i);
		contact[Contact::get_contact_count()].init(data);

		return ;
	}
}
