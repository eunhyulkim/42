/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 04:59:30 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void			conv_s_init(t_tab *tab)
{
	char		*str;

	if (!(str = va_arg(tab->ap, char *)))
		tab->content = ft_strdup("(null)");
	else
		tab->content = ft_strdup(str);
	unuse_flag(" +#", tab);
}

void			handle_sharp(t_tab *tab)
{
	char		*str;
	int			cnt;

	str = (char *)tab->content;
	if ((cnt = get_sharp(tab)) < (int)ft_strlen(str))
		str = ft_strremove(str, &str[cnt], 0);
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
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_s(t_tab *tab)
{
	if (tab->size == 'l')
	{
		conversion_ws(tab);
		return ;
	}
	conv_s_init(tab);
	if (has_sharp(tab))
		handle_sharp(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
}
