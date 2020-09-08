/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:46:06 by yopark            #+#    #+#             */
/*   Updated: 2020/09/08 12:19:07 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

extern fd_set read_set;
extern fd_set write_set;

Client::Client(int fd, struct sockaddr_in addr): _fd(fd), _addr(addr)
{
	fcntl(_fd, F_SETFL, O_NONBLOCK);
	FD_SET(_fd, &read_set);
	FD_SET(_fd, &write_set);
	std::cout << "client constructor" << std::endl;
}

Client::~Client()
{
	close(_fd);
	std::cout << "client destructor" << std::endl;
}

int			Client::getFd() const
{
	return (_fd);
}