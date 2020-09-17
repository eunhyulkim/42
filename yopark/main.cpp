/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:46:42 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 19:36:06 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"

#include <iostream>
#include <list>
#include <sys/select.h>
#include <algorithm>

fd_set read_set;
fd_set write_set;
fd_set error_set;
fd_set read_set_copy;
fd_set write_set_copy;
fd_set error_set_copy;
bool live = true;


void			kill_server(int signal)
{
	(void)signal;
	std::cout << std::endl;
	live = false;
}


int			main(int argc, char *argv[])
{
	signal(SIGINT, kill_server);

	FD_ZERO(&read_set_copy);
	FD_ZERO(&write_set_copy);
	FD_ZERO(&error_set_copy);

	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	std::list<Server*> servers = ws::parseConfig();

	while (live)
	{
		read_set = read_set_copy;
		write_set = write_set_copy;
		error_set = error_set_copy;
		
		int max_fd = 0;

		for (std::list<Server*>::iterator it = servers.begin() ; it != servers.end() ; ++it)
			max_fd = std::max(max_fd, (*it)->getMaxfd());
		int n = select(max_fd + 1, &read_set, &write_set, &error_set, &timeout);
		if (n == -1)
		{
			std::cerr << "select error" << std::endl;
			exit(1);
		}
		else if (n == 0)
		{
			continue ;
		}
		for (std::list<Server*>::iterator sev = servers.begin() ; sev != servers.end() ; ++sev)
		{
			if (FD_ISSET((*sev)->getFd(), &read_set))
				(*sev)->putClient();
			for (std::list<Client*>::iterator cli = (*sev)->clients.begin() ; cli != (*sev)->clients.end() ; ++cli)
			{
				if (FD_ISSET((*cli)->getFd(), &read_set))
					(*sev)->recvRequest(*cli);
				if (FD_ISSET((*cli)->getFd(), &write_set))
					(*sev)->sendResponse(*cli);
			}
		}
	}
	for (std::list<Server*>::iterator it = servers.begin() ; it != servers.end() ; ++it)
		delete *it;
	return (0);
}