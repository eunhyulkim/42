#ifndef ERROR_HPP
# define ERROR_HPP

# include <string>
# include <iostream>

class Error
{
	private:
		/* declare member variable */
	public:
		Error();
		Error(const std::string& /* parameter */, ...);
		Error(const Error& copy);
		Error& operator=(const Error& obj);
		virtual ~Error();

		/* declare member function */
		/* exception declare */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Error& error);

#endif
