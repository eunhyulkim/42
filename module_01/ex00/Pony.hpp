/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:57:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 01:24:56 by eunhkim          ###   ########.fr       */
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
		bool		parent_alive;
	public:
		Pony(std::string _name = "Noname", std::string _color = "White",
		int _age = 1, bool _parent_alive = true)
		 : name(_name), color(_color), age(_age), parent_alive(_parent_alive){};

		static void 	ponyOnTheStack();
		static void 	ponyOnTheHeap();

		std::string get_name(void);
		std::string get_color(void);
		int get_age(void);
		bool get_parent_alive(void);
		void speak();
		void go_to_the_future(int years);
};
#endif
