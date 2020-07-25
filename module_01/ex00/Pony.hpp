/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:57:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/25 20:02:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONY_HPP
# define PONY_HPP

/*
** LIB
*/
# include <iostream>

/*
** Class Prototype
*/
class Pony;

/*
** Class Definition
*/
class Pony {
	private:
		std::string name;
		std::string	color;
		int			age;
	public:

/*
** Function Prototype
*/
void 	ponyOnTheHeap();
void 	ponyOnTheStack();

#endif
