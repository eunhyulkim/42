/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:01:45 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 22:45:40 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	const void * address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << std::hex << address;
	this->address = ss.str();
}

std::string	Brain::identify(void)
{
	return (this->address);
}
