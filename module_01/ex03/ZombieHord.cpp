/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHord.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 10:55:45 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 12:08:16 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieHord.hpp"

ZombieHord::ZombieHord(int size)
{
	this->_size = size;
	this->_zombies = new Zombie[3];
	this->announce();
}

ZombieHord::~ZombieHord(void)
{
	std::cout << this->_zombies;
	delete[] this->_zombies;
}

int ZombieHord::get_size(void)
{
	return (this->_size);
}

void ZombieHord::announce(void)
{
	for (int i = 0; i < this->_size; i++)
		this->_zombies[i].announce();
}
