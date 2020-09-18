#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <iostream>

class Config
{
	private:
		std::string m_software_name;
		std::string m_software_version;
		std::string m_http_version;
		std::string m_cgi_version;
		char **m_base_env;
	public:
		Config();
		Config(const std::string& /* parameter */, ...);
		Config(const Config& copy);
		Config& operator=(const Config& obj);
		virtual ~Config();

		/* declare member function */
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Config& config);

#endif
