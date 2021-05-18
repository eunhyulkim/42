#include "phonebook.hpp"

int Contact::count = 0;

void Contact::init(Form& form)
{
	for (int i = 0; i < 11; i++)
		data[i] = form.get_input(i);
	count += 1;
}

int Contact::get_contact_count(void)
{
	return (Contact::count);
}

void Contact::add_contact_count(int value)
{
	Contact::count += value;
	return ;
}

Contact& Contact::get_last_contact(Contact *contact)
{
	return (contact[Contact::get_contact_count() - 1]);
}

std::string Contact::get_data(int nth)
{
	return (data[nth]);
}

void Contact::set_data(int nth, std::string src)
{
	data[nth] = src;
	return ;
}
