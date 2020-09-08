/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:43:07 by yopark            #+#    #+#             */
/*   Updated: 2020/09/08 01:05:37 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <arpa/inet.h>

class Client
{
private:
	int						_fd;
	struct sockaddr_in		_addr;

	Client();
public:
	Client(int fd, struct sockaddr_in addr);
	virtual ~Client();

	int			getFd() const;
};

#endif