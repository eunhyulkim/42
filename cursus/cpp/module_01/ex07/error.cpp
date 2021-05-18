/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:01:12 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 01:23:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

namespace error{
	void	exit(char const *msg)
	{
		if (msg)
			std::cout << msg << std::endl;
		std::exit(EXIT_FAILURE);
	}

	void	exit(std::string msg)
	{
		if (!msg.empty())
			std::cout << msg << std::endl;
		std::exit(EXIT_FAILURE);
	}
}
