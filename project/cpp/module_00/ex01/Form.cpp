#include "phonebook.hpp"

const std::string Form::field[11] = {
	"first_name",
	"last_name",
	"nickname",
	"login_id",
	"postal_address",
	"email_address",
	"phone_number",
	"birtyday_date",
	"favorite_meal",
	"underware_color",
	"darkest_secret"
};

const std::string Form::guide[11] = {
	"Enter first name(Required).",
	"Enter last name(Required).",
	"Enter nickname(Required).",
	"Enter login_id(Required).",
	"Enter postal_address(Optional).",
	"Enter email_address(Optional).",
	"Enter phone_number(Optional, 11 digit with '-'.",
	"Enter birtyday_date(Optional, OOOO-OO-OO).",
	"Enter favorite_meal(Optional).",
	"Enter underware_color(Optional).",
	"Enter darkest_secret(Optional)."
};

const std::string Form::get_field(int i)
{
	return (Form::field[i]);
}

std::string Form::get_input(int i)
{
	return (input[i]);
}

/*
** mendatory_field_no = 0~3
*/
void Form::get_mendatory_field(int field_no)
{
	std::string		text;

	do {
		std::cout << Form::guide[field_no] << std::endl;
		if (!std::getline(std::cin, text))
			throw (CTRL_D_ERR);
	} while (text.empty());
	input[field_no] = text;
}

/*
** post_field_no = 4, 8~10
*/
void Form::get_generic_field(int field_no)
{
	std::string		text;

	std::cout << Form::guide[field_no] << std::endl;
	if (!std::getline(std::cin, text))
		throw (CTRL_D_ERR);
	input[field_no] = text;
}

void Form::get_email_field(int field_no)
{
	std::string		text;
	bool			res;

	res = false;
	do {
		std::cout << Form::guide[field_no] << std::endl;
		if (!std::getline(std::cin, text))
			throw (CTRL_D_ERR);
		if (text.find("@") != std::string::npos \
		&& text.find("@") == text.rfind("@") \
		&& text.find("@") != 0 && text.find("@") != text.size() - 1)
			res = true;
		if (text.empty())
			res = true;
	} while (!res);
	input[field_no] = text;
}

void Form::get_phonenumber_field(int field_no)
{
	std::string		text;

	do {
		std::cout << Form::guide[field_no] << std::endl;
		if (!std::getline(std::cin, text))
			throw (CTRL_D_ERR);
		if (text.empty())
			break ;
		if (text.size() != 13)
			continue;
		if (std::count(text.begin(), text.end(), '-') != 2)
			continue;
		if (text.find("-") != 3|| text.rfind("-") != 8)
			continue;
		for (unsigned long i = 0; i < text.size(); i++)
			if ((text.at(i) < '0' || text.at(i) > '9') && text.at(i) != '-')
				continue;
		break ;
	} while (true);
	input[field_no] = text;
}

void Form::get_birthday_field(int field_no)
{
	std::string		text;

	do {
		std::cout << Form::guide[field_no] << std::endl;
		if (!std::getline(std::cin, text))
			throw (CTRL_D_ERR);
		if (text.empty())
			break ;
		if (text.size() != 10)
			continue;
		if (std::count(text.begin(), text.end(), '-') != 2)
			continue;
		if (text.find("-") != 4|| text.rfind("-") != 7)
			continue;
		for (unsigned long i = 0; i < text.size(); i++)
			if ((text.at(i) < '0' || text.at(i) > '9') && text.at(i) != '-')
				continue;
		break ;
	} while (true);
	input[field_no] = text;
}
