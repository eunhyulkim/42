/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:46:06 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 16:47:08 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

extern fd_set read_set_copy;
extern fd_set write_set_copy;

Client::Client(int fd, struct sockaddr_in addr): _fd(fd), _addr(addr)
{
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "fcntl error" << std::endl;
		exit(1);
	}
	FD_SET(_fd, &read_set_copy);
	std::cout << "Client constructor" << " [" << htons(_addr.sin_port) << "]" << std::endl;
}

Client::~Client()
{
	close(_fd);
	std::cout << "Client destructor" << " [" << htons(_addr.sin_port) << "]" << std::endl;
}

int			Client::getFd() const
{
	return (_fd);
}