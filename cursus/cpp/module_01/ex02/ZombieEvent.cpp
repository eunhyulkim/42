/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 10:55:45 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:26:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieEvent.hpp"

void
ZombieEvent::setZombieType(std::string type) {
	this->_type = type;
}

Zombie*
ZombieEvent::newZombie(std::string name) {
	return (new Zombie(this->_type, name));
}

Zombie*
ZombieEvent::randomChump(void) {
	Zombie *zombie = new Zombie("child");
	zombie->announce();
	return (zombie);
}

void	ZombieEvent::fightYourParent(Zombie *&z)
{
	std::cout << "<" << z->get_name() << "(" << z->get_type() << ")" << ">"
	<< " I can't win to Super Zombie." << std::endl;
	std::cout << "<" << z->get_name() << "(" << z->get_type() << ")" << ">"
	<< " I'm dying..." << std::endl;
	delete z;
	z = nullptr;
}
