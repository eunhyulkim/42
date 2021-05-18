/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:39:26 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/17 04:39:26 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Config::Config() 
: m_software_name(),
m_software_version(),
m_http_version(),
m_cgi_version(),
m_base_env(NULL) {}

Config::Config(std::string config_block, char** env)
{
	std::map<std::string, std::string> map_block = ft::stringVectorToMap(ft::split(config_block, '\n'), ' ');
	this->m_software_name = map_block.find("SOFTWARE_NAME")->second;
	this->m_software_version = map_block.find("SOFTWARE_VERSION")->second;
	this->m_http_version = map_block.find("HTTP_VERSION")->second;
	this->m_cgi_version = map_block.find("CGI_VERSION")->second;
	this->m_base_env = env;
}

Config::Config(const Config& copy)
: m_software_name(copy.get_m_software_name()),
m_software_version(copy.get_m_software_version()),
m_http_version(copy.get_m_http_version()),
m_cgi_version(copy.get_m_cgi_version()),
m_base_env(copy.get_m_base_env()) {}

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
	this->m_base_env = obj.get_m_base_env();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Config& config)
{
	out << "SOFTWARE_NAME: " << config.get_m_software_name() << std::endl
	<< "SOFTWARE_VERSION: " << config.get_m_software_version() << std::endl
	<< "HTTP_VERSION: " << config.get_m_http_version() << std::endl
	<< "CGI_VERSION: " << config.get_m_cgi_version() << std::endl
	<< "CGI_ENVARIABLE:" << std::endl;
	char **env = config.get_m_base_env();
	while (env && *env) {
		std::cout << *env << std::endl;
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
char **Config::get_m_base_env() const { return (this->m_base_env); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
