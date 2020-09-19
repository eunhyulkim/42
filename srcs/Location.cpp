#include "Location.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Location::Location() {}
Location::Location(std::string location_block)
{
	std::map<std::string, std::string> map_block = ft::stringVectorToMap(ft::split(location_block, '\n'), ' ');
	this->m_root_path = map_block.find("root")->second;
	if (ft::hasKey(map_block, "auth_basic_realm"))
		this->m_auth_basic_realm = map_block.find("auth_basic_realm")->second;
	if (ft::hasKey(map_block, "auth_basic_file"))
		this->m_auth_basic_file = map_block.find("auth_basic_file")->second;
	if (ft::hasKey(map_block, "allow_method"))
		this->m_allow_method = ft::stringVectorToSet(ft::split(map_block.find("allow_method")->second, ' '));
	else {
		this->m_allow_method.insert("GET");
		this->m_allow_method.insert("POST");
	}
	this->m_index = ft::stringVectorToSet(ft::split(map_block.find("index")->second, ' '));
	this->m_cgi = ft::stringVectorToSet(ft::split(map_block.find("cgi")->second, ' '));
	this->m_autoindex = ft::hasKey(map_block, "autoindex") && map_block.find("autoindex")->second == "on";
}

Location::Location(const Location& copy) 
{
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
	out << "ROOT_PATH: " << location.get_m_root_path() << std::endl;
	out << "AUTH_BASIC_REALM: " << location.get_m_auth_basic_realm() << std::endl;
	out << "AUTH_BASIC_FILE: " << location.get_m_auth_basic_file() << std::endl;
	out << "ALLOW_METHOD: " << ft::setToString(location.get_m_allow_method()) << std::endl;
	out << "INDEX: " << ft::setToString(location.get_m_index()) << std::endl;
	out << "CGI: " << ft::setToString(location.get_m_cgi()) << std::endl;
	out << "AUTOINDEX: " << std::boolalpha << location.get_m_autoindex()<< std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Location::get_m_root_path() const { return (this->m_root_path); }
std::string Location::get_m_auth_basic_realm() const { return (this->m_auth_basic_realm); }
std::string Location::get_m_auth_basic_file() const { return (this->m_auth_basic_file); }
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
