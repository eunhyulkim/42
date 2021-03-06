/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 10:55:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/30 16:23:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_EVENT_HPP
# define ZOMBIE_EVENT_HPP

#include <iostream>

class ZombieEvent;

class ZombieEvent
{
	private:
		std::string _type;
	public:
		void	setZombieType(std::string type);
		Zombie	*randomChump(void);
		Zombie	*newZombie(std::string name);
		void	fightYourParent(Zombie *&z);
};
#endif
