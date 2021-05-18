/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:08:15 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:43:11 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type){
	this->type = type;
}

void	Weapon::setType(std::string type){
	this->type = type;
}

std::string	Weapon::get_type(void){
	return (this->type);
}
