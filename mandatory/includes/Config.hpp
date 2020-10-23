/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:40:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/17 04:40:20 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		char**		m_base_env;
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
		char **get_m_base_env() const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Config& config);

#endif
