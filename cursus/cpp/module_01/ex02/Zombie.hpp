/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:51:46 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:25:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <random>

class Zombie
{
	private:
		static int		idx;
		std::string		_type;
		std::string		_name;

	public:
		Zombie(std::string type = "super", std::string name = "");
		void 		announce(void);
		std::string	get_name();
		std::string	get_type();
};

#endif
