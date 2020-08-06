/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:29:46 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/06 11:05:12 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

namespace replace
{
	void	to_new_file(std::string origin, char *av[])
	{
		std::ofstream out(std::string(av[1]).append(".replace"));
		std::string before = av[2];
		std::string after = av[3];

		while (origin.find(before) != std::string::npos)
		{
			int idx = origin.find(before);
			out << origin.substr(0, idx);
			out << after;
			origin.assign(origin.substr(idx + before.size()));
		}
		if (!origin.empty())
			out << origin;
	}
}
