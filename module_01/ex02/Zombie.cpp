/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:43 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:17:58 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int Zombie::idx = 0;

namespace {
	std::string keyword_list[] ={"love",
								"kill",
								"see",
								"bed with",
								"sleep",
								"eat",
								"kick",
								"present death for",
								"change",
								"talk with"};
	std::string alphabet_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string alphabet_lower = "abddefghijklmnopqrstuvwxyz";

	std::string name_list[] =	{"Zoker",
								"Skinner",
								"Mad Zombie",
								"Smart Zaombie",
								"Bouncer",
								"Mob Zombie",
								"Horde Zombie",
								"Radical Zombie",
								"Forager",
								"Burster"};

	std::string get_random_name()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> name_dis(0, 9);
		return (name_list[name_dis(gen)]);
	}

	void cout_announce_message()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> alpha_dis(0, 25);
		std::uniform_int_distribution<int> num_dis(2, 5);
		std::uniform_int_distribution<int> msg_dis(0, 9);
		std::cout << alphabet_upper[alpha_dis(gen)];
		std::cout << std::string(num_dis(gen), alphabet_lower[alpha_dis(gen)]);
		std::cout << std::string(2, '.');
		std::cout << " I'm going to " << keyword_list[msg_dis(gen)];
		std::cout << " you...";
	}
}

Zombie::Zombie(std::string type, std::string name) : _type(type), _name(name)
{
	this->idx += 1;
	if (name == "")
		_name = get_random_name();
};

std::string Zombie::get_name(void){
	return (this->_name);
}

std::string Zombie::get_type(void){
	return (this->_type);
}

void Zombie::announce(void)
{
	std::cout << "<" << this->_name << "("
	<< this->_type << ")" << ">" << " ";
	cout_announce_message();
	std::cout << std::endl;
}
