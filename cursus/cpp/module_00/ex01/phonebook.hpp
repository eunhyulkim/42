#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# define CTRL_D_ERR		"CTRL+D ENTERED"

# include <iostream>
# include <fstream>
# include <iomanip>
# include "Form.hpp"
# include "Contact.hpp"

namespace print {
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
