/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:55:16 by yopark            #+#    #+#             */
/*   Updated: 2020/09/08 12:17:39 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"

# include <arpa/inet.h>
# include <list>
# include <string>

class Server
{
private:
	int						_fd;
	struct sockaddr_in		_addr;
	
public:
	std::list<Client*>		clients;

	Server(const char *ip, int port);
	virtual ~Server();

	Server		&operator=(const Server &x);

	int			getFd() const;
	int			getMaxfd() const;

	void		putClient();
	void		recvRequest(Client *cli);
	void		sendResponse(Client *cli);
};

#endif