/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:39:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:32:00 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void			put_flag(char c, t_tab *tab)
{
	if (c == '0')
		tab->flag[0] = 1;
	if (c == ' ')
		tab->flag[1] = 1;
	if (c == '+')
		tab->flag[2] = 1;
	if (c == '-')
		tab->flag[3] = 1;
	if (c == '#')
		tab->flag[4] = 1;
	return ;
}

int				has_flag(char c, t_tab *tab)
{
	if (c == '0' && tab->flag[0] == 1)
		return (1);
	if (c == ' ' && tab->flag[1] == 1)
		return (1);
	if (c == '+' && tab->flag[2] == 1)
		return (1);
	if (c == '-' && tab->flag[3] == 1)
		return (1);
	if (c == '#' && tab->flag[4] == 1)
		return (1);
	return (0);
}

void			unuse_flag(char *set, t_tab *tab)
{
	int			i;

	i = 0;
	while (set[i])
	{
		if (has_flag(set[i], tab))
		{
			if (set[i] == '0')
				tab->flag[0] = 0;
			else if (set[i] == ' ')
				tab->flag[1] = 0;
			else if (set[i] == '+')
				tab->flag[2] = 0;
			else if (set[i] == '-')
				tab->flag[3] = 0;
			else if (set[i] == '#')
				tab->flag[4] = 0;
		}
		i++;
	}
}

static void		flag_rule_handle(t_tab *tab)
{
	if (has_flag('-', tab))
		unuse_flag("0", tab);
	if (has_flag('+', tab))
		unuse_flag(" ", tab);
}

void			check_flag(t_tab *tab)
{
	char		*str;

	str = tab->treat;
	while (ft_isset(*str, "0 +-#"))
	{
		if (*str == '0')
			tab->flag[0] = 1;
		else if (*str == ' ')
			tab->flag[1] = 1;
		else if (*str == '+')
			tab->flag[2] = 1;
		else if (*str == '-')
			tab->flag[3] = 1;
		else if (*str == '#')
			tab->flag[4] = 1;
		str++;
	}
	flag_rule_handle(tab);
	tab->treat = str;
}
