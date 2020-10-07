#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "webserv.hpp"

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
        size_t m_limit_client_body_size;
        bool m_autoindex;
		Location();
	public:
		Location(const std::string& location_uri, std::string location_block, size_t server_limit_client_body_size);
		Location(const Location& copy);
		Location& operator=(const Location& obj);
		virtual ~Location();

		/* getter function */
        std::string get_m_uri() const;
        std::string get_m_root_path() const;
        std::string get_m_auth_basic_realm() const;
        const std::map<std::string, std::string>& get_m_auth_basic_file() const;
        std::set<std::string> get_m_allow_method() const;
        const std::set<std::string>& get_m_index() const;
        const std::set<std::string>& get_m_cgi() const;
        const bool& get_m_autoindex() const;
        size_t get_m_limit_client_body_size() const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Location& location);

#endif
