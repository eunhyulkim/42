/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:34:17 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/10 10:55:25 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** static void		clear_terminal(void)
** {
** 	ft_putstr_fd("\033[H\033[J", 1);
** }
*/

static int		print_ascii_art(void)
{
	char	*line;
	int		fd;

	if ((fd = open(ASCIIART_PATH, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line))
	{
		ft_putstr_fd(line, 1);
		free(line);
	}
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\n", 1);
	free(line);
	close(fd);
	return (1);
}

/*
**TODO: config option control
**clear_terminal();
*/

void			display_logo(void)
{
	if (!(print_ascii_art()))
		ft_putstr_fd("Failed print ascii art\n", 1);
}

void			display_prompt(void)
{
	ft_putstr_fd("mongshell$ ", 1);
}
