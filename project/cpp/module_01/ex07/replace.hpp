/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 01:00:43 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/27 01:31:25 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

namespace error {
	void	exit(char const *msg);
	void	exit(std::string msg);
}

namespace replace{
	void	to_new_file(std::string origin, char *av[]);
}
