/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 04:59:08 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		handle_sharp(t_tab *tab)
{
	char		*str;
	t_uint		cnt;
	t_uint		len;

	str = (char *)tab->content;
	if (has_sharp(tab) && !get_sharp(tab))
	{
		if (ft_strlen(str) == 3 && str[2] == '0')
			str = ft_strfreedup(str, "0x");
		return ;
	}
	if ((int)get_sharp(tab) <= (int)ft_strlen((char *)tab->content) - 2)
		return ;
	len = (int)get_sharp(tab) - ((int)ft_strlen(str) - 2);
	cnt = len;
	while (cnt--)
		str = ft_strmjoin(ft_strdup("0"), str);
	ft_swapc(&str[len + 1], &str[1]);
	tab->content = str;
	return ;
}

static void		handle_width(t_tab *tab)
{
	char		*str;
	char		*gap;
	char		c[2];
	t_uint		cnt;

	c[0] = has_flag('0', tab) ? '0' : ' ';
	c[1] = 0;
	str = (char *)tab->content;
	cnt = tab->width - (int)ft_strlen((char *)str);
	gap = (char *)malloc(sizeof(char) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(char) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_strmjoin(str, gap);
	else
		str = ft_strmjoin(gap, str);
	if (has_flag('0', tab))
		ft_swapc(&str[cnt + 1], &str[1]);
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_p(t_tab *tab)
{
	t_ulint		addr_nb;
	char		*str;

	unuse_flag(" +#", tab);
	if (has_sharp(tab))
		unuse_flag("0", tab);
	addr_nb = (t_ulint)va_arg(tab->ap, void *);
	str = ft_trans_base(addr_nb, "0123456789abcdef");
	tab->content = ft_strmjoin(ft_strdup("0x"), str);
	if (has_sharp(tab))
		handle_sharp(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
}
