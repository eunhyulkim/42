/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:42:39 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 19:33:24 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sstream>

extern fd_set read_set_copy;
extern fd_set write_set_copy;

Server::Server(int port)
{
	if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		std::cerr << "socket error" << std::endl;
		exit(1);
	}

	int value = true;

	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
	{
		std::cerr << "setsockopt error" << std::endl;
		exit(1);
	}

	bzero(&_addr, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(_fd, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(struct sockaddr)) == -1)
	{
		std::cerr << "bind error" << std::endl;
		exit(1);
	}

	if (listen(_fd, 42) == -1)
	{
		std::cerr << "listen error" << std::endl;
		exit(1);
	}

	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "fcntl error" << std::endl;
		exit(1);
	}
	FD_SET(_fd, &read_set_copy);
	std::cout << "Server constructor" << " [" << htons(_addr.sin_port) << "]" << std::endl;
}

Server::~Server()
{
	close(_fd);
	for (std::list<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
		delete *it;
	std::cout << "Server destructor" << " [" << htons(_addr.sin_port) << "]" << std::endl;
}

Server		&Server::operator=(const Server &x)
{
	_fd = x._fd;
	_addr = x._addr;
	clients = x.clients;
	return (*this);
}


int			Server::getFd() const
{
	return (_fd);
}

int			Server::getMaxfd() const
{
	int		max_fd = _fd;

	for (std::list<Client*>::const_iterator it = clients.begin() ; it != clients.end() ; ++it)
			max_fd = std::max(max_fd, (*it)->getFd());
	return (max_fd);
}

void		Server::putClient()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size = sizeof(struct sockaddr_in);
	Client				*cli;

	bzero(&client_addr, client_addr_size);

	int client_fd;

	if ((client_fd = accept(_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
	{
		std::cerr << "accept error" << std::endl;
		exit(1);
	}
	cli = new Client(client_fd, client_addr);
	clients.push_back(cli);
}

void		Server::_parseRequest(const std::string &raw)
{
	std::istringstream	is(raw);
	std::string			line;
	int					signal = 0;

	std::stringstream	body;
	
	body.str("");

	while (std::getline(is, line, '\n'))
	{
		if (signal == 0)
		{
			std::istringstream	is2(line);
			std::string			line2;
			int					signal2 = 0;

			while (std::getline(is2, line2, ' '))
			{
				if (signal2 == 0) request.method = line2;
				else if (signal2 == 1) request.uri = line2;
				else if (signal2 == 2) request.version = line2;
				else {};
				signal2++;
			}
			signal++;
		}
		else if (signal == 1)
		{
			if (line == "")
			{
				signal++;
				continue ;
			}
			size_t			pos = line.find(":");
			std::string		key = line.substr(0, pos);
			std::string		value = line.substr(pos + 1, line.length() - pos);

			request.headers.insert(std::make_pair(key, value));
		}
		else if (signal == 2)
		{
			body << line;
		}
	}
	request.body = body.str();
}


void		Server::recvRequest(Client *cli)
{
	char	buf[1000];

	int n = recv(cli->getFd(), buf, 1000, 0);
	if (!n)
		return ;
	buf[n] = '\0';		
	_parseRequest(std::string(buf));

	std::cout << "method:" << request.method << std::endl;
	std::cout << "uri:" << request.uri << std::endl;
	std::cout << "version:" << request.version << std::endl;
	for (std::map<std::string, std::string>::iterator it = request.headers.begin() ; it != request.headers.end() ; ++it)
		std::cout << "key:" << it->first << " " << "value:" << it->second << std::endl;
	std::cout << "body:" << request.body << std::endl;

	FD_SET(cli->getFd(), &write_set_copy);
}

void		Server::sendResponse(Client *cli)
{
	char msg[] = "HTTP/1.1 200 OK\r\nContent-Length: 25\r\n\r\n<p>welcome, 42 webserver!</p>";

	send(cli->getFd(), msg, strlen(msg), 0);
	FD_CLR(cli->getFd(), &write_set_copy);
}
