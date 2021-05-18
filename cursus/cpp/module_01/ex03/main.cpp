/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:54 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/01 11:35:48 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieHord.hpp"

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}

	void welcome_msg(void)
	{
		std::cout << std::endl;
		std::cout << "WELCOME TO ZOMBIE WORLD!" << std::endl;
		std::cout << "In our world, 10 zombies that never die!" << std::endl;
	}
}

int main(void)
{
	welcome_msg();
	{
		print("SUPER ZOMBIE CREATE(With Random Name)");
		Zombie superZombie[4];

		print("ZOMBIE HORD CREATE(With Random Name)");
		ZombieHord hord(5);

		print("ZOMBIE HORD ANNOUNCE");
		hord.announce();

		print("ZOMBIE HORD MASS SUICIDE");
		hord.massSuicide();

		print("TEST END");
	}
	return (0);
}
