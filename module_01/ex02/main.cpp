/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:31:14 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieEvent.hpp"

namespace {
	void welcome_msg(void)
	{
		std::cout << std::endl;
		std::cout << "WELCOME TO ZOMBIE WORLD!" << std::endl;
		std::cout << "In our world, 10 zombies that never die!" << std::endl;
	}

	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}

	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	welcome_msg();
	print("SUPER ZOMBIE CREATE(With Random Name)");
	Zombie superZombie[10];
	print("SUPER ZOMBIE ANNOUNCE(name, type, crying)");
	for (int i = 0; i < 10; i++)
		superZombie[i].announce();
	print("ZOMBIE EVENT CREATE");
	ZombieEvent event;

	print("SET ZOMBIE TYPE TO CHILD");
	event.setZombieType("Child");
	print("CREATE NEW ZOMBIE ON HEAP");
	Zombie* childZombie = event.newZombie("K7");
	print("CREATE NEW ZOMBIE ON HEAP WITH RANDOM CHUMP");
	Zombie* randomChumpZombie = event.randomChump();

	print("GO TO FIGHT WITH PARENT ZOMBIE");
	event.fightYourParent(childZombie);
	event.fightYourParent(randomChumpZombie);

	print("DELETE CHECK TEST");
	std::cout << childZombie << std::endl;
	std::cout << randomChumpZombie << std::endl;

	print("TEST END");
	return (0);
}
