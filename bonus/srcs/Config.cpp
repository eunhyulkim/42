#include "Config.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Config::Config() {
	this->m_base_env = NULL;
}

bool
Config::loadPlugin(std::vector<std::string> plugins)
{
	for (size_t i = 0; i < plugins.size(); ++i)
	{
		std::string plugin = ft::trim(plugins[i], " ");
		if (plugin == "echo" || plugin == "Echo")
			m_plugin_echo = true;
		else if (plugin == "alm" || plugin == "ALM")
			m_plugin_alm = true;
		else if (plugin == "array-var" || plugin == "Array-Var")
			m_plugin_array_var = true;
		else if (plugin == "health-check" || plugin == "Health-Check")
			m_plugin_health_check = true;
		else if (plugin == "log-if" || plugin == "Log-If")
			m_plugin_log_if = true;
		else if (plugin == "basic-auth" || plugin == "Basic-Auth")
			m_plugin_basic_auth = true;
		else if (plugin == "cache" || plugin == "Cache")
			m_plugin_cache = true;
		else if (plugin == "filter" || plugin == "Filter")
			m_plugin_filter = true;
		else
			return (false);
	}
	return (true);
}

Config::Config(std::string config_block, char** env)
{
	std::map<std::string, std::string> map_block = ft::stringVectorToMap(ft::split(config_block, '\n'), ' ');
	this->m_software_name = map_block.find("SOFTWARE_NAME")->second;
	this->m_software_version = map_block.find("SOFTWARE_VERSION")->second;
	this->m_http_version = map_block.find("HTTP_VERSION")->second;
	this->m_cgi_version = map_block.find("CGI_VERSION")->second;
	this->m_plugin_echo = false;
	this->m_plugin_alm = false;
	this->m_plugin_array_var = false;
	this->m_plugin_health_check = false;
	this->m_plugin_log_if = false;
	this->m_plugin_basic_auth = false;
	this->m_plugin_cache = false;
	this->m_plugin_filter = false;
	this->m_base_env = env;

	if (ft::hasKey(map_block, "PLUGIN")) 
		loadPlugin(ft::split(map_block["PLUGIN"], '|'));	
}

Config::Config(const Config& copy)
: m_software_name(copy.get_m_software_name()),
m_software_version(copy.get_m_software_version()),
m_http_version(copy.get_m_http_version()),
m_cgi_version(copy.get_m_cgi_version()),
m_plugin_echo(copy.is_on_plugin_echo()),
m_plugin_alm(copy.is_on_plugin_alm()),
m_plugin_array_var(copy.is_on_plugin_array_var()),
m_plugin_health_check(copy.is_on_plugin_health_check()),
m_plugin_log_if(copy.is_on_plugin_log_if()),
m_plugin_basic_auth(copy.is_on_plugin_basic_auth()),
m_plugin_cache(copy.is_on_plugin_cache()),
m_plugin_filter(copy.is_on_plugin_filter()),
m_base_env(copy.get_m_base_env())
{}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Config::~Config()
{
	this->m_software_name.clear();
	this->m_software_version.clear();
	this->m_http_version.clear();
	this->m_cgi_version.clear();
	this->m_base_env = NULL;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Config&
Config::operator=(const Config& obj)
{
	if (this == &obj)
		return (*this);
	this->m_software_name = obj.get_m_software_name();
	this->m_software_version = obj.get_m_software_version();
	this->m_http_version = obj.get_m_http_version();
	this->m_cgi_version = obj.get_m_cgi_version();
	this->m_plugin_echo = obj.is_on_plugin_echo();
	this->m_plugin_alm = obj.is_on_plugin_alm();
	this->m_plugin_array_var = obj.is_on_plugin_array_var();
	this->m_plugin_health_check = obj.is_on_plugin_health_check();
	this->m_plugin_log_if = obj.is_on_plugin_log_if();
	this->m_plugin_basic_auth = obj.is_on_plugin_basic_auth();
	this->m_plugin_cache = obj.is_on_plugin_cache();
	this->m_plugin_filter = obj.is_on_plugin_filter();
	this->m_base_env = obj.get_m_base_env();

	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Config& config)
{
	out << "SOFTWARE_NAME: " << config.get_m_software_name() << std::endl
	<< "SOFTWARE_VERSION: " << config.get_m_software_version() << std::endl
	<< "HTTP_VERSION: " << config.get_m_http_version() << std::endl
	<< "CGI_VERSION: " << config.get_m_cgi_version() << std::endl;
	char **env = config.get_m_base_env();
	while (*env) {
		++env;
	}
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Config::get_m_software_name() const { return (this->m_software_name); }
std::string Config::get_m_software_version() const { return (this->m_software_version); }
std::string Config::get_m_http_version() const { return (this->m_http_version); }
std::string Config::get_m_cgi_version() const { return (this->m_cgi_version); }
bool Config::is_on_plugin_echo() const { return (this->m_plugin_echo); }
bool Config::is_on_plugin_alm() const { return (this->m_plugin_alm); }
bool Config::is_on_plugin_array_var() const { return (this->m_plugin_array_var); }
bool Config::is_on_plugin_health_check() const { return (this->m_plugin_health_check); }
bool Config::is_on_plugin_log_if() const { return (this->m_plugin_log_if); }
bool Config::is_on_plugin_basic_auth() const { return (this->m_plugin_basic_auth); }
bool Config::is_on_plugin_cache() const { return (this->m_plugin_cache); }
bool Config::is_on_plugin_filter() const { return (this->m_plugin_filter); }
char **Config::get_m_base_env() const { return (this->m_base_env); }
Config *Config::clone() { return (new Config(*this)); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
