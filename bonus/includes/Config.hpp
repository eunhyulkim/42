#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

class Config
{
	private:
		std::string m_software_name;
		std::string m_software_version;
		std::string m_http_version;
		std::string m_cgi_version;
		bool m_plugin_echo;
		bool m_plugin_alm;
		bool m_plugin_array_var;
		bool m_plugin_health_check;
		bool m_plugin_log_if;
		bool m_plugin_basic_auth;
		bool m_plugin_cache;
		bool m_plugin_filter;
		char **m_base_env;
	public:
		Config();
		Config(std::string config_block, char **env);
		Config(const Config& copy);
		Config& operator=(const Config& obj);
		virtual ~Config();

		/* getter function */
		std::string get_m_software_name() const;
		std::string get_m_software_version() const;
		std::string get_m_http_version() const;
		std::string get_m_cgi_version() const;
		bool is_on_plugin_echo() const;
		bool is_on_plugin_alm() const;
		bool is_on_plugin_array_var() const;
		bool is_on_plugin_health_check() const;
		bool is_on_plugin_log_if() const;
		bool is_on_plugin_basic_auth() const;
		bool is_on_plugin_cache() const;
		bool is_on_plugin_filter() const;
		char **get_m_base_env() const;

		bool loadPlugin(std::vector<std::string> plugins);
		Config* clone();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Config& config);

#endif
