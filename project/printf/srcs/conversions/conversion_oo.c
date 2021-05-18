/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_oo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 05:09:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		handle_width(t_tab *tab)
{
	char		*str;
	char		*gap;
	char		c[2];
	t_uint		cnt;

	c[0] = (has_flag('0', tab)) ? '0' : ' ';
	c[1] = 0;
	str = (char *)tab->content;
	cnt = tab->width - 1;
	gap = (char *)malloc(sizeof(char) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(char) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_strmjoin(str, gap);
	else
		str = ft_strmjoin(gap, str);
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_oo(t_tab *tab)
{
	char		c[2];

	c[1] = 0;
	c[0] = '%';
	unuse_flag(" +#", tab);
	tab->content = ft_strdup(c);
	tab->count = 1;
	if (tab->width > 1)
		handle_width(tab);
}
