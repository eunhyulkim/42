/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:42:39 by yopark            #+#    #+#             */
/*   Updated: 2020/09/08 13:03:32 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>

extern fd_set read_set;

Server::Server(const char *ip, int port)
{
	if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) // 소켓 생성
	{
		std::cerr << "socket error" << std::endl;
		exit(1);
	}
	std::cout << "socket succeed" << std::endl;

	int value = true;

	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1) // 소켓 옵션 부여
	{
		std::cerr << "setsockopt error" << std::endl;
		exit(1);
	}
	std::cout << "setsockopt succeed" << std::endl;

	bzero(&_addr, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET; // AF_INET = PF_INET, IP 주소 체계를 인터넷 프로토콜뿐만 아니라 다른 프로토콜에서도 사용할 수 있도록 함
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip);
	if (bind(_fd, reinterpret_cast<struct sockaddr *>(&_addr), sizeof(struct sockaddr)) == -1) // 소켓에 주소 할당
	{
		std::cerr << "bind error" << std::endl;
		exit(1);
	}
	std::cout << "bind succeed" << std::endl;

	if (listen(_fd, 42) == -1) // 소켓 열기
	{
		std::cerr << "listen error" << std::endl;
		exit(1);
	}
	std::cout << "listen succeed" << std::endl;

	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1) // O_NONBLOCK 플래그 설정
	{
		std::cerr << "fcntl error" << std::endl;
		exit(1);
	}
	std::cout << "fcntl succeed" << std::endl;
	FD_SET(_fd, &read_set); // read_set.fd_array[_fd] = true;
	std::cout << "Server constructor" << std::endl;
}

Server::~Server()
{
	close(_fd);
	for (std::list<Client*>::iterator it = clients.begin() ; it != clients.end() ; ++it)
		delete *it;
	std::cout << "Server destructor" << std::endl;
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
	Client				*a;

	bzero(&client_addr, client_addr_size);

	int client_fd;

	if ((client_fd = accept(_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
	{
		std::cerr << "accept error" << std::endl;
		exit(1);
	}
	std::cout << "accept succeed" << std::endl;
	a = new Client(client_fd, client_addr);
	clients.push_back(a);
}

void		Server::recvRequest(Client *cli)
{
	char	buf[1000];

	int n = recv(cli->getFd(), buf, 1000, 0);
	buf[n] = '\0';
	std::cout << buf << std::endl;
}

void		Server::sendResponse(Client *cli)
{
	char msg[] = "HTTP/1.1 200 OK\r\nContent-Length: 25\r\n\r\n<p>welcome, 42 webserver!</p>";

	send(cli->getFd(), msg, strlen(msg), 0);
}




// int		Server::readRequest(std::vector<Client*>::iterator it)
// {
// 	int 		bytes;
// 	int			ret;
// 	Client		*client = NULL;
// 	std::string	log;

// 	client = *it;
// 	bytes = strlen(client->rBuf);
// 	ret = read(client->fd, client->rBuf + bytes, BUFFER_SIZE - bytes);
// 	bytes += ret;
// 	if (ret > 0)
// 	{
// 		client->rBuf[bytes] = '\0';
// 		if (strstr(client->rBuf, "\r\n\r\n") != NULL
// 			&& client->status != Client::BODYPARSING)
// 		{
// 			log = "REQUEST:\n";
// 			log += client->rBuf;
// 			g_logger.log(log, HIGH);
// 			client->last_date = ft::getDate();
// 			_handler.parseRequest(*client, _conf);
// 			client->setWriteState(true);
// 		}
// 		if (client->status == Client::BODYPARSING)
// 			_handler.parseBody(*client);
// 		return (1);
// 	}
// 	else
// 	{
// 		*it = NULL;
// 		_clients.erase(it);
// 		if (client)
// 			delete client;
// 		g_logger.log("[" + std::to_string(_port) + "] " + "connected clients: " + std::to_string(_clients.size()), LOW);
// 		return (0);
// 	}
// }

// int		Server::writeResponse(std::vector<Client*>::iterator it)
// {
// 	unsigned long	bytes;
// 	std::string		tmp;
// 	std::string		log;
// 	Client			*client = NULL;

// 	client = *it;
// 	switch (client->status)
// 	{
// 		case Client::RESPONSE:
// 			log = "RESPONSE:\n";
// 			log += client->response.substr(0, 128);
// 			g_logger.log(log, HIGH);
// 			bytes = write(client->fd, client->response.c_str(), client->response.size());
// 			if (bytes < client->response.size())
// 				client->response = client->response.substr(bytes);
// 			else
// 			{
// 				client->response.clear();
// 				client->setToStandBy();
// 			}
// 			client->last_date = ft::getDate();
// 			break ;
// 		case Client::STANDBY:
// 			if (getTimeDiff(client->last_date) >= TIMEOUT)
// 				client->status = Client::DONE;
// 			break ;
// 		case Client::DONE:
// 			delete client;
// 			_clients.erase(it);
// 			g_logger.log("[" + std::to_string(_port) + "] " + "connected clients: " + std::to_string(_clients.size()), LOW);
// 			return (0);
// 		default:
// 			_handler.dispatcher(*client);
// 	}
// 	return (1);
// }
