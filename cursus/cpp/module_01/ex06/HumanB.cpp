/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:46:24 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:50:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name){}

void	HumanB::setWeapon(Weapon &club)
{
	this->weapon = &club;
}

void	HumanB::attack(void)
{
	std::cout << this->name << " " << "attacks with his ";
	std::cout << weapon->get_type() << std::endl;
}
