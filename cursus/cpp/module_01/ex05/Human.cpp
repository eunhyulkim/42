/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 22:00:17 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 22:56:20 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

Brain& Human::getBrain(void)
{
	return (this->humanBrain);
}

std::string	Human::identify(void)
{
	return (this->getBrain().identify());
}
