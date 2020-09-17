/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 17:55:16 by yopark            #+#    #+#             */
/*   Updated: 2020/09/11 18:32:36 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "utils.hpp"

# include <arpa/inet.h>
# include <list>
# include <string>

class Server
{
private:
	int						_fd;
	struct sockaddr_in		_addr;

	void					_parseRequest(const std::string &raw);

public:
	std::list<Client*>		clients;
	ws::Request				request;
	ws::Response			response;

	Server(int port);
	virtual ~Server();

	Server		&operator=(const Server &x);

	int			getFd() const;
	int			getMaxfd() const;

	void		putClient();
	void		recvRequest(Client *cli);
	void		sendResponse(Client *cli);
};

#endif