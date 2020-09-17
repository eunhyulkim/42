/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:38:04 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 19:44:44 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Server.hpp"

#include <iostream>
#include <fstream>

std::list<Server*>		ws::parseConfig()
{
	std::list<Server*>		servers;
	std::fstream			fs;

	fs.open("conf/webserv.conf");
	if (!fs.is_open())
	{
		std::cerr << "conf open error" << std::endl;
		exit(1);
	}

	Server					*a = new Server(4000);
	Server					*b = new Server(4001);

	servers.push_back(a);
	servers.push_back(b);

	fs.close();
	return (servers);
}

const std::string		ws::makeStatusCode(int n)
{
	if (n / 100 == 1)
	{
		if (n == 100) return std::string("100 Continue");
		if (n == 101) return std::string("101 Switching Protocols");
	}
	else if (n / 100 == 2)
	{
		if (n == 200) return std::string("200 OK");
		if (n == 201) return std::string("201 Created");
		if (n == 202) return std::string("202 Accepted");
		if (n == 203) return std::string("203 Non-Authoritative Information");
		if (n == 204) return std::string("204 No Content");
		if (n == 205) return std::string("205 Reset Content");
		if (n == 206) return std::string("206 Partial Content");
	}
	else if (n / 100 == 3)
	{
		if (n == 300) return std::string("300 Multiple Choices");
		if (n == 301) return std::string("301 Moved Permanently");
		if (n == 302) return std::string("302 Found");
		if (n == 303) return std::string("303 See Other");
		if (n == 304) return std::string("304 Not Modified");
		if (n == 305) return std::string("305 Use Proxy");
		if (n == 306) return std::string("306 Switch Proxy");
		if (n == 307) return std::string("307 Temporary Redirect");
	}
	else if (n / 100 == 4)
	{
		if (n == 400) return std::string("400 Bad Request");
		if (n == 401) return std::string("401 Unauthorized");
		if (n == 402) return std::string("402 Payment Required");
		if (n == 403) return std::string("403 Forbidden");
		if (n == 404) return std::string("404 Not Found");
		if (n == 405) return std::string("405 Method Not Allowed");
		if (n == 406) return std::string("406 Not Acceptable");
		if (n == 407) return std::string("407 Proxy Authentication Required");
		if (n == 408) return std::string("408 Request Timeout");
		if (n == 409) return std::string("409 Conflict");
		if (n == 410) return std::string("410 Gone");
		if (n == 411) return std::string("411 Length Required");
		if (n == 412) return std::string("412 Precondition Failed");
		if (n == 413) return std::string("413 Payload Too Large");
		if (n == 414) return std::string("414 URI Too Long");
		if (n == 415) return std::string("415 Unsupported Media Type");
		if (n == 416) return std::string("416 Range Not Satisfiable");
		if (n == 417) return std::string("417 Expectation Failed");
		if (n == 426) return std::string("426 Upgrade Required");
	}
	else if (n / 100 == 5)
	{
		if (n == 500) return std::string("500 Internal Server Error");
		if (n == 501) return std::string("501 Not Implemented");
		if (n == 502) return std::string("502 Bad Gateway");
		if (n == 503) return std::string("503 Service Unavailable");
		if (n == 504) return std::string("504 Gateway Timeout");
		if (n == 505) return std::string("505 HTTP Version Not Supported");
	}
	return (NULL);
}

