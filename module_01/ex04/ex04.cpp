/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 12:12:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:51:05 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace {
	void	print(char const *msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}

	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
}

int main(void)
{
	std::string	str = "HI THIS IS BRAIN";
	std::string *str_pointer = &str;
	std::string &str_reference = str;

	print("DEFAULT TEXT");
	std::cout << str << std::endl;
	print("PRINT TEXT IN POINTER");
	std::cout << *str_pointer << std::endl;
	print("PRINT TEXT IN REFERNCE");
	std::cout << str_reference << std::endl;
	return (0);
}
