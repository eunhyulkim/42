/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 05:09:30 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		conv_wc_init(t_tab *tab)
{
	t_uchar		*c;
	t_uint		wc;

	c = (t_uchar *)malloc(sizeof(t_uchar) * 4);
	ft_memset(c, 0, sizeof(c));
	wc = va_arg(tab->ap, wint_t);
	if (wc <= 127 && (tab->count = 1))
		c[0] = (t_uchar)wc;
	else if (wc <= 2047 && (tab->count = 2))
		c[0] = (wc >> 6) + 192;
	else if (wc < 65535 && (tab->count = 3))
		c[0] = (wc >> 12) + 224;
	else if (wc <= 65535 && (tab->count = 4))
	{
		c[0] = (wc >> 18) + 240;
		c[1] = ((wc >> 12) & 63) + 128;
	}
	if (tab->count > 2)
		c[tab->count - 2] = ((wc >> 6) & 63) + 128;
	if (tab->count > 1)
		c[tab->count - 1] = ((wc & 63) + 128);
	tab->count = (wc == 0) ? 0 : tab->count;
	tab->content = c;
	unuse_flag(" +#", tab);
}

static void		handle_width(t_tab *tab)
{
	t_uchar		*str;
	t_uchar		*gap;
	t_uchar		c[2];
	t_uint		cnt;
	t_uint		len;

	c[0] = has_flag('0', tab) ? '0' : ' ';
	c[1] = 0;
	str = tab->content;
	len = tab->count;
	cnt = (len != 0) ? (tab->width - tab->count) : tab->width;
	gap = (t_uchar *)malloc(sizeof(t_uchar) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(t_uchar) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_ustrmjoin(str, gap);
	else
		str = ft_ustrmjoin(gap, str);
	if (!len && has_flag('-', tab))
		str[0] = 0;
	else if (!len)
		str[tab->width - 1] = 0;
	tab->content = str;
	return ;
}

void			conversion_wc(t_tab *tab)
{
	conv_wc_init(tab);
	if (tab->width > tab->count)
		handle_width(tab);
	tab->count = (tab->count < tab->width) ? tab->width : tab->count;
	tab->count = (tab->count == 0) ? 1 : tab->count;
}
