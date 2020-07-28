/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:27 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 00:51:27 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

std::string Pony::get_name(void){
	return (name);
}

std::string Pony::get_color(void){
	return (color);
}

int Pony::get_age(void){
	return (age);
}

bool Pony::get_parent_alive(void){
	return (parent_alive);
}

void Pony::go_to_the_future(int years){
	age += years;
	if (age >= 20)
		parent_alive = false;
}

void Pony::speak(void){
	std::cout << "my color is " << color
	<< ", and my age is " << age << "." << std::endl;
	std::cout << "my parents are ";
	if (parent_alive)
		std::cout << "alive!" << std::endl;
	else
		std::cout << "died..." << std::endl;
}

void 	Pony::ponyOnTheStack(void)
{
	Pony apony;
	std::cout << "Hello, I'm a " << apony.get_name() << " living on the stack." << std::endl;
	apony.speak();

	std::cout << std::endl;

	Pony bpony("eunhkim");
	std::cout << "Hello, I'm a " << bpony.get_name() << " living on the stack." << std::endl;
	bpony.speak();
}

void 	Pony::ponyOnTheHeap(void)
{
	Pony *cpony = new Pony("hurre", "blue");
	std::cout << "Hello, I'm a " << cpony->get_name() << " living on the heap." << std::endl;
	cpony->speak();

	std::cout << std::endl;

	cpony->go_to_the_future(20);
	std::cout << "Hello, I'm a " << cpony->get_name() << " living on the heap." << std::endl;
	cpony->speak();
	delete cpony;
}
