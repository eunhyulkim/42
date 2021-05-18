/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:47:20 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		conv_c_init(t_tab *tab)
{
	t_uchar		c[2];

	ft_memset(c, 0, sizeof(c));
	c[0] = va_arg(tab->ap, int);
	tab->content = ft_strdup((char *)c);
	unuse_flag(" +#", tab);
}

static void		handle_width(t_tab *tab)
{
	char		*str;
	char		*gap;
	char		c[2];
	t_uint		cnt;
	t_uint		len;

	c[0] = has_flag('0', tab) ? '0' : ' ';
	c[1] = 0;
	str = (char *)tab->content;
	len = ft_strlen(str);
	cnt = (len != 0) ? (tab->width - 1) : tab->width;
	gap = (char *)malloc(sizeof(char) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(char) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_strmjoin(str, gap);
	else
		str = ft_strmjoin(gap, str);
	if (!len && has_flag('-', tab))
		str[0] = 0;
	else if (!len)
		str[tab->width - 1] = 0;
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_c(t_tab *tab)
{
	if (tab->size == 'l')
	{
		conversion_wc(tab);
		return ;
	}
	conv_c_init(tab);
	tab->count = 1;
	if (tab->width > 1)
		handle_width(tab);
}
