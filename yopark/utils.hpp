/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:34:38 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 19:44:22 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <map>
# include <list>

class Server;

namespace ws
{
	struct Request
	{
		std::string							method;
		std::string							uri;
		std::string							version;
		std::map<std::string, std::string>	headers;
		std::string							body;
	};

	struct Response
	{
		std::string							version;
		int									statusCode;
		std::map<std::string, std::string>	headers;
		std::string							body;
	};

	std::list<Server*>		parseConfig();
	const std::string		makeStatusCode(int n);
}

#endif