/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:22:26 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:41:27 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& club) : name(name), weapon(club){}

void	HumanA::attack(void)
{
	std::cout << this->name << " " << "attacks with his ";
	std::cout << weapon.get_type() << std::endl;
}
