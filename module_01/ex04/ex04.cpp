/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 12:12:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 12:14:43 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void)
{
	std::string	str = "HI THIS IS BRAIN";
	std::string *str_pointer = &str;
	std::string &str_reference = str;

	std::cout << *str_pointer << std::endl;
	std::cout << str_reference << std::endl;
	return (0);
}
