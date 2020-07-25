#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# define ASCIIART_PATH	"srcs/asciiart"
# define CTRL_D_ERR		"CTRL+D ENTERED"

# include <iostream>
# include <fstream>
# include <iomanip>

class Form;
class Contact;

class Form {
	private:
		static const std::string	guide[11];
		static const std::string	field[11];
		std::string					input[11];
	public:
		static const std::string get_field(int i);
		std::string get_input(int i);
		void get_mendatory_field(int field_no);
		void get_generic_field(int field_no);
		void get_email_field(int filed_no);
		void get_phonenumber_field(int field_no);
		void get_birthday_field(int field_no);
};

class Contact {
	private:
		std::string	data[11];
		static int count;
	public:
		void init(Form& form);
		std::string get_data(int nth);
		void set_data(int nth, std::string src);
		static void add_contact_count(int value);
		static Contact& get_last_contact(Contact *contact);
		static int get_contact_count(void);

};

namespace print {
	void	login_art(void);
	void	message(char const *msg);
	void	message(std::string msg);
	void	not_valid_cmd(void);
}

namespace execute {
	int		exit(void);
	void	add(Contact *contact);
	void	search(Contact *contact);
	void 	show_contact_list(Contact *contact);
}
# endif
