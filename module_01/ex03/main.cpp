/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:54 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:51:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieHord.hpp"

namespace {
	void welcome_msg(void)
	{
		std::cout << std::endl;
		std::cout << "WELCOME TO ZOMBIE WORLD!" << std::endl;
		std::cout << "In our world, 10 zombies that never die!" << std::endl << std::endl;
	}

	void leaks_test(void)
	{
		Zombie superZombie[4];
		welcome_msg();

		ZombieHord hord;
		return ;
	}
}

int main(void)
{
	leaks_test();
	return (0);
}
