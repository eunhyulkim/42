#ifndef CONTACT_HPP
# define CONTACT_HPP

class Contact;

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

#endif
