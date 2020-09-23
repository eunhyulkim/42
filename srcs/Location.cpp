#include "Location.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Location::Location() {}
Location::Location(const std::string& location_uri, std::string location_block)
: m_uri(location_uri)
{
	std::map<std::string, std::string> map_block = ft::stringVectorToMap(ft::split(location_block, '\n'), ' ');
	this->m_root_path = map_block.find("root")->second;
	if (ft::hasKey(map_block, "auth_basic_realm"))
		this->m_auth_basic_realm = map_block.find("auth_basic_realm")->second;
	if (ft::hasKey(map_block, "auth_basic_file")) {
		std::vector<std::string> content = ft::split(ft::getStringFromFile(map_block.find("auth_basic_file")->second), '\n');
		for (size_t i = 0; i < content.size(); ++i) {
			std::vector<std::string> v = ft::split(content[i]);
			if (v.size() != 2 || ft::trim(v[0]).empty() || ft::trim(v[1]).empty())
				throw std::invalid_argument("auth_basic_file format is invalid");
			std::string key = ft::trim(v[0]);
			std::string value = ft::trim(v[1]);
			this->m_auth_basic_file[key] = value;
		}
	}
	if (ft::hasKey(map_block, "allow_method"))
		this->m_allow_method = ft::stringVectorToSet(ft::split(map_block.find("allow_method")->second, ' '));
	else {
		this->m_allow_method.insert("GET");
		this->m_allow_method.insert("HEAD");
	}
	if (ft::hasKey(map_block, "index"))
		this->m_index = ft::stringVectorToSet(ft::split(map_block.find("index")->second, ' '));
	if (ft::hasKey(map_block, "cgi"))
		this->m_cgi = ft::stringVectorToSet(ft::split(map_block.find("cgi")->second, ' '));
	this->m_autoindex = ft::hasKey(map_block, "autoindex") && map_block.find("autoindex")->second == "on";
}

Location::Location(const Location& copy) 
{
	this->m_uri = copy.get_m_uri();
	this->m_root_path = copy.get_m_root_path();
	this->m_auth_basic_realm = copy.get_m_auth_basic_realm();
	this->m_auth_basic_file = copy.get_m_auth_basic_file();
	this->m_allow_method = copy.get_m_allow_method();
	this->m_index = copy.get_m_index();
	this->m_cgi = copy.get_m_cgi();
	this->m_autoindex = copy.get_m_autoindex();
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Location::~Location()
{
	this->m_uri.clear();
	this->m_root_path.clear();
	this->m_auth_basic_realm.clear();
	this->m_auth_basic_file.clear();
	this->m_allow_method.clear();
	this->m_index.clear();
	this->m_cgi.clear();
	this->m_autoindex = false;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Location& Location::operator=(const Location& obj)
{
	if (this == &obj)
		return (*this);
	this->m_uri = obj.get_m_uri();
	this->m_root_path = obj.get_m_root_path();
	this->m_auth_basic_realm = obj.get_m_auth_basic_realm();
	this->m_auth_basic_file = obj.get_m_auth_basic_file();
	this->m_allow_method = obj.get_m_allow_method();
	this->m_index = obj.get_m_index();
	this->m_cgi = obj.get_m_cgi();
	this->m_autoindex = obj.get_m_autoindex();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Location& location)
{
	out << "URI: " << location.get_m_uri() << std::endl;
	out << "ROOT_PATH: " << location.get_m_root_path() << std::endl;
	out << "AUTH_BASIC_REALM: " << location.get_m_auth_basic_realm() << std::endl;
	out << "ALLOW_METHOD: " << ft::containerToString(location.get_m_allow_method()) << std::endl;
	out << "INDEX: " << ft::containerToString(location.get_m_index()) << std::endl;
	out << "CGI: " << ft::containerToString(location.get_m_cgi()) << std::endl;
	out << "AUTOINDEX: " << std::boolalpha << location.get_m_autoindex()<< std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Location::get_m_uri() const { return (this->m_uri); }
std::string Location::get_m_root_path() const { return (this->m_root_path); }
std::string Location::get_m_auth_basic_realm() const { return (this->m_auth_basic_realm); }
const std::map<std::string, std::string>& Location::get_m_auth_basic_file() const { return (this->m_auth_basic_file); }
const std::set<std::string>& Location::get_m_allow_method() const { return (this->m_allow_method); }
const std::set<std::string>& Location::get_m_index() const { return (this->m_index); }
const std::set<std::string>& Location::get_m_cgi() const { return (this->m_cgi); }
const bool& Location::get_m_autoindex() const { return (this->m_autoindex); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
