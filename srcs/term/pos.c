/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:30:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 22:30:00 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	get_cursor_start_pos(t_line *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	match_move(int key_pressed, t_line *line)
{
	int					i;
	static t_keymove	keymove[8] = {
		{KEY_RIGHT, &cursor_to_right},
		{KEY_LEFT, &cursor_to_left},
		{KEY_HOME, &cursor_to_home},
		{KEY_END, &cursor_to_end},
		{KEY_SRIGHT, &goto_next_word},
		{KEY_SLEFT, &goto_prev_word},
		{KEY_SPREVIOUS, &goto_prev_line},
		{KEY_SNEXT, &goto_next_line}
	};

	i = 0;
	while (i < 8)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
}
