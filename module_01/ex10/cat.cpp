/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:23:42 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/01 11:53:23 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cat.hpp"

namespace cat {
	void	from_stdin(void)
	{
		std::string	line;

		while (std::getline(std::cin, line))
			std::cout << line << std::endl;
	}

	void	from_files(int ac, char *av[])
	{

		for (int i = 1; i < ac; i++)
		{
			std::ifstream in(av[i]);
			if (!in.is_open())
			{
				std::cout << "cat: " << av[i]
				<< ": No Such file or directory" << std::endl;
				continue;
			}

			std::string	line;
			std::string data;
			while (std::getline(in, line))
				data.append(line).push_back('\n');
			std::cout << data;
			in.close();
		}
	}
}
