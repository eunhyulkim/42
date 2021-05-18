/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:23 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/01 11:34:28 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"
#include <unistd.h>

#define LEAK_DEBUG	true
namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	print("PonyOnTheStack(default, eunhkim)");
	Pony::ponyOnTheStack();

	print("PonyOnTheHeap(eunhkim) with goToTheFuture");
	Pony::ponyOnTheHeap();

	if (LEAK_DEBUG)
		sleep(60);
	return (0);
}
