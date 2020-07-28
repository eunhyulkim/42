/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:51:39 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieEvent.hpp"

namespace {
	void welcome_msg(void)
	{
		std::cout << std::endl;
		std::cout << "WELCOME TO ZOMBIE WORLD!" << std::endl;
		std::cout << "In our world, 10 zombies that never die!" << std::endl << std::endl;
	}
}

int main(void)
{
	Zombie superZombie[10];
	welcome_msg();
	ZombieEvent event;

	event.setZombieType("Child");
	Zombie* childZombie = event.newZombie("K7");

	event.fightYourParent(childZombie);
	return (0);
}
