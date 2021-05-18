/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHord.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 10:55:45 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:47:05 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieHord.hpp"

ZombieHord::ZombieHord(int size)
{
	this->_size = size;
	this->_zombies = new Zombie[size];
}

ZombieHord::~ZombieHord(void)
{
	if (this->_zombies)
	{
		delete[] this->_zombies;
		this->_zombies = nullptr;
	}
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

void ZombieHord::massSuicide(void)
{
	if (this->_zombies)
	{
		delete[] this->_zombies;
		this->_zombies = nullptr;
	}
}
