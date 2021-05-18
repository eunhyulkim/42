#ifndef FORM_HPP
# define FORM_HPP

class Form;

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

#endif
