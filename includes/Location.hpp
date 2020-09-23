#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <set>
# include <map>
# include <iostream>
# include "libft.hpp"

class Location
{
	private:
        std::string m_uri;
		std::string m_root_path;
		std::string m_auth_basic_realm;
        std::map<std::string, std::string> m_auth_basic_file;
		std::set<std::string> m_allow_method;
        std::set<std::string> m_index;
        std::set<std::string> m_cgi;
        bool m_autoindex;
		Location();
	public:
		Location(const std::string& location_uri, std::string location_block);
		Location(const Location& copy);
		Location& operator=(const Location& obj);
		virtual ~Location();

		/* getter function */
        std::string get_m_uri() const;
        std::string get_m_root_path() const;
        std::string get_m_auth_basic_realm() const;
        const std::map<std::string, std::string>& get_m_auth_basic_file() const;
        const std::set<std::string>& get_m_allow_method() const;
        const std::set<std::string>& get_m_index() const;
        const std::set<std::string>& get_m_cgi() const;
        const bool& get_m_autoindex() const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Location& location);

#endif
