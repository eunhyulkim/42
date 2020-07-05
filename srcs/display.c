/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:34:17 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/04 15:14:33 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_terminal(void)
{
	ft_putstr_fd("\033[H\033[J", 1);
}

int				print_ascii_art(void)
{
	char	*line;
	int		fd;

	if ((fd = open("config/mongshell_ascii_art", O_RDONLY)) < 0)
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

void			display_logo(void)
{
	//TODO: config option control
	//clear_terminal();
	if (!(print_ascii_art()))
		ft_putstr_fd("Failed print ascii art\n", 1);
}

void			display_prompt(void)
{
	char *prompt_str;

	prompt_str = "mongshell$ ";
	ft_putstr_fd(prompt_str, 1);
}


