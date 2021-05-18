/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gim-eunhyul <gim-eunhyul@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:34 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/07 21:05:44 by gim-eunhyul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	memoryLeak()
{
	std::string* panther = new std::string("String panther");

	std::cout << *panther << std::endl;
	delete panther;
}
