/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_ws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 05:10:02 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static size_t	ft_wtoua(wchar_t wc, t_uchar **c)
{
	t_uint		cnt;

	cnt = (wc <= 127) ? 1 : 0;
	cnt = (cnt == 0 && wc <= 2047) ? 2 : cnt;
	cnt = (cnt == 0 && wc <= 65535) ? 3 : cnt;
	cnt = (cnt == 0) ? 4 : cnt;
	*c = (t_uchar *)malloc(sizeof(t_uchar) * cnt);
	ft_memset(*c, 0, sizeof(*c));
	if (cnt == 1)
		(*c)[0] = (t_uchar)wc;
	else if (cnt == 2)
		(*c)[0] = (wc >> 6) + 192;
	else if (cnt == 3)
		(*c)[0] = (wc >> 12) + 224;
	else if (cnt == 4)
	{
		(*c)[0] = (wc >> 18) + 240;
		(*c)[1] = ((wc >> 12) & 63) + 128;
	}
	if (cnt > 2)
		(*c)[cnt - 2] = ((wc >> 6) & 63) + 128;
	if (cnt > 1)
		(*c)[cnt - 1] = ((wc & 63) + 128);
	return (cnt);
}

static void		conv_ws_init(t_tab *tab)
{
	wchar_t		*ws;
	t_uchar		*s1;
	t_uchar		*s2;
	int			i;
	t_uchar		size[2];

	unuse_flag(" +#", tab);
	if (!(ws = va_arg(tab->ap, wchar_t *)))
	{
		tab->content = ft_ustrdup((t_uchar *)"(null)");
		tab->count = 6;
		return ;
	}
	size[1] = 0;
	s1 = 0;
	s2 = 0;
	i = -1;
	while (ws[++i])
	{
		tab->count += 1;
		size[0] = (t_uchar)ft_wtoua(ws[i], &s2);
		tab->w_size = ft_ustrmjoin(tab->w_size, ft_ustrdup(size));
		s1 = ft_ustrmjoin(s1, s2);
	}
	tab->content = s1;
}

static void		handle_sharp(t_tab *tab)
{
	t_uchar		*str;
	t_uint		cnt;
	t_uint		i;

	str = (t_uchar *)tab->content;
	if (ft_ustrlen(str) <= (size_t)get_sharp(tab))
		return ;
	if (tab->w_size == 0)
	{
		tab->content = ft_ustrremove(str, &str[get_sharp(tab)]);
		tab->count = get_sharp(tab);
		return ;
	}
	i = 0;
	cnt = 0;
	while (cnt <= (t_uint)get_sharp(tab))
		cnt += (t_uint)tab->w_size[i++];
	cnt -= (t_uint)tab->w_size[--i];
	tab->count = i;
	str = ft_ustrremove(str, &str[cnt]);
	tab->content = str;
	return ;
}

static void		handle_width(t_tab *tab)
{
	t_uchar		*str;
	t_uchar		*gap;
	t_uchar		c[2];
	t_uint		cnt;

	str = tab->content;
	if (ft_ustrlen(str) >= tab->width)
		return ;
	c[0] = has_flag('0', tab) ? '0' : ' ';
	c[1] = 0;
	cnt = tab->width - ft_ustrlen(str);
	gap = (t_uchar *)malloc(sizeof(t_uchar) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(t_uchar) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_ustrmjoin(str, gap);
	else
		str = ft_ustrmjoin(gap, str);
	tab->content = str;
	if (tab->w_size == 0)
		tab->count = tab->width;
	return ;
}

void			conversion_ws(t_tab *tab)
{
	conv_ws_init(tab);
	if (has_sharp(tab))
		handle_sharp(tab);
	if (tab->width)
		handle_width(tab);
}
