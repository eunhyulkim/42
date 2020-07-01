/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:23:35 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/30 21:20:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	int fd;
	fd = open("result.txt", O_WRONLY | O_APPEND);
	printf("HELLO");
	printf("ERROR");
	return (0);
}

// PIPE