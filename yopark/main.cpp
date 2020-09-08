/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:46:42 by yopark            #+#    #+#             */
/*   Updated: 2020/09/08 12:21:45 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

#include <iostream>
#include <list>
#include <sys/select.h>
#include <algorithm>

fd_set read_set;
fd_set write_set;
fd_set error_set;

int			main(int argc, char *argv[])
{
	std::list<Server*> servers;

	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	FD_ZERO(&read_set); // bzero(&read_set, sizeof(fd_set));
	FD_ZERO(&write_set);
	FD_ZERO(&error_set);

	Server *a = new Server("127.0.0.1", 4000);
	Server *b = new Server("127.0.0.1", 4001);

	servers.push_back(a);
	servers.push_back(b);

	fd_set read_set_copy = read_set;
	fd_set write_set_copy = write_set;
	fd_set error_set_copy = error_set;

	while (true)
	{
		read_set = read_set_copy;
		write_set = write_set_copy;
		error_set = error_set_copy;
		
		int max_fd = 0;

		for (std::list<Server*>::iterator it = servers.begin() ; it != servers.end() ; ++it)
			max_fd = std::max(max_fd, (*it)->getMaxfd());
		std::cout << max_fd << std::endl;
		int n = select(max_fd + 1, &read_set, &write_set, &error_set, &timeout);
		if (n == -1)
		{
			std::cerr << "select error" << std::endl;
			exit(1);
		}
		else if (n == 0)
		{
			std::cout << "no fds are ready for 1 second" << std::endl;
			continue ;
		}
		for (std::list<Server*>::iterator it = servers.begin() ; it != servers.end() ; ++it)
		{
			if (FD_ISSET((*it)->getFd(), &read_set)) // read_set.fd_array[it->getFd()] == true
				(*it)->putClient();
			for (std::list<Client*>::iterator cli = (*it)->clients.begin() ; cli != (*it)->clients.end() ; ++cli)
			{
				if (FD_ISSET((*cli)->getFd(), &read_set))
					(*it)->recvRequest(*cli);
				if (FD_ISSET((*cli)->getFd(), &write_set))
					(*it)->sendResponse(*cli);
			}
		}
	}
	for (std::list<Server*>::iterator it = servers.begin() ; it != servers.end() ; ++it)
		delete *it;
	return (0);
}