/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:23 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:51:24 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

int main(void)
{
	Pony::ponyOnTheStack();
	std::cout << std::endl;
	Pony::ponyOnTheHeap();
	return (0);
}
