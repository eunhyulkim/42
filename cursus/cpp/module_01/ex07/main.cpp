/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 00:54:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 02:18:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

namespace {
	void	check_valid_args(char *av[], std::string &origin)
	{
		std::string line;
		std::string msg;

		std::ifstream in(av[1]);
		if (!in.is_open())
			error::exit("filename is unvalid");
		while (getline(in, line))
			origin.append(line).push_back('\n');
		if (origin.empty())
			error::exit("srcs file is empty");
		if (origin.find(av[2]) == std::string::npos)
			error::exit(std::string().assign("Don't find substring ").append(av[1]));
		if (std::string(av[2]) == std::string(av[3]))
			error::exit("origin and replace keyword is same");
	}
}

int		main(int ac, char *av[])
{
	std::string		origin;

	if (ac != 4)
		error::exit("argument count is unvalid");
	check_valid_args(av, origin);
	replace::to_new_file(origin, av);
	return (0);
}
