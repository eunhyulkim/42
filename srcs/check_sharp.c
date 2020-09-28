/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sharp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:39:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/10 01:49:35 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		get_sharp(t_tab *tab)
{
	return (tab->sharp[1]);
}

int		has_sharp(t_tab *tab)
{
	return (tab->sharp[0]);
}

void	check_sharp(t_tab *tab)
{
	char	*str;
	int		sharp;

	str = tab->treat;
	if (*str == '.')
	{
		tab->sharp[0] = 1;
		str++;
		if (ft_isnum(*str))
			tab->sharp[1] = ft_moveatoll(&str);
		else if (*str == '*')
		{
			if ((sharp = va_arg(tab->ap, int)) < 0)
				tab->sharp[0] = 0;
			tab->sharp[1] = sharp;
			str++;
		}
	}
	tab->treat = str;
}
