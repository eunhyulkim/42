/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHord.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 10:55:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/26 11:52:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HORD_HPP
# define ZOMBIE_HORD_HPP

#include <iostream>
#include "Zombie.hpp"

class ZombieHord;

class ZombieHord
{
	private:
		Zombie 		*_zombies;
		int			_size;
	public:
		ZombieHord(int size = 1);
		~ZombieHord(void);
		int 		get_size(void);
		void 		announce(void);
};
#endif
