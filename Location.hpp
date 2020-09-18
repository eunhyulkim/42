#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <iostream>

class Location
{
	private:
		m_root_path;
		m_allow_method;
		m_auth_basic_realm;
		m_auth_basic_file;
		m_index;
		m_cgi;
		m_autoindex;
	public:
		Location();
		Location(const std::string& /* parameter */, ...);
		Location(const Location& copy);
		Location& operator=(const Location& obj);
		virtual ~Location();

		/* declare member function */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Location& location);

#endif
