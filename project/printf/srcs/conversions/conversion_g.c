/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_g.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:26:47 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/11 21:21:42 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		conv_g_init(t_tab *tab)
{
	t_llint		nb;
	double		n;
	t_uint		len;
	int			i;

	if ((len = 6) && has_sharp(tab))
		len = get_sharp(tab) ? get_sharp(tab) : 1;
	n = va_arg(tab->ap, double);
	nb = n;
	tab->content = ft_etoa(n, len - 1, 1);
	i = ft_atoll(ft_strnstr((char *)tab->content, "e", \
		ft_strlen((char *)tab->content)) + 1);
	if (i < (int)len && i >= -4)
	{
		free(tab->content);
		if (ft_digit(nb) >= (int)len)
			tab->content = ft_ftoa(n, 0);
		else
			tab->content = ft_lftovna(n, len);
	}
	if (!tab->content)
		return (0);
	if (((char *)tab->content)[0] == '-')
		unuse_flag(" ", tab);
	return (1);
}

static void		handle_trail(t_tab *tab)
{
	char		*str;
	int			cnt;

	str = (char *)tab->content;
	if (!ft_strchr(str, '.') && ft_strchr(str, 'e'))
		str = ft_strinsert(str, "e", ".");
	else if (!ft_strchr(str, '.'))
		str = ft_strmjoin(str, ft_strdup("."));
	cnt = has_sharp(tab) ? get_sharp(tab) : 6;
	cnt = (cnt == 0) ? 1 : cnt;
	cnt -= ft_strchr(str, 'e') ? ft_strchr(str, 'e') - str - 1 : 0;
	while (ft_strchr(str, 'e') && (cnt-- > 0))
		str = ft_strinsert(str, "e", "0");
	cnt -= !ft_strchr(str, 'e') ? (int)ft_strlen(str) - 1 : 0;
	while (cnt-- > 0)
		str = ft_strmjoin(str, ft_strdup("0"));
	tab->content = str;
}

static void		handle_sign(t_tab *tab)
{
	char		*str;

	str = (char *)tab->content;
	if (has_flag('+', tab) && (str[0] != '-'))
		str = ft_strmjoin(ft_strdup("+"), str);
	else if (has_flag(' ', tab) && str[0] != '-')
		str = ft_strmjoin(ft_strdup(" "), str);
	tab->content = str;
	return ;
}

static void		handle_width(t_tab *tab)
{
	char		*str;
	char		*gap;
	char		c[2];
	t_uint		cnt;

	str = (char *)tab->content;
	c[0] = has_flag('0', tab) ? '0' : ' ';
	c[1] = 0;
	cnt = tab->width - ft_strlen(str);
	gap = (char *)malloc(sizeof(char) * (cnt + 1));
	ft_memset(gap, c[0], sizeof(char) * (cnt + 1));
	gap[cnt] = 0;
	if (has_flag('-', tab))
		str = ft_strmjoin(str, gap);
	else
		str = ft_strmjoin(gap, str);
	if (has_flag('0', tab) && ft_isset(str[cnt], "+- "))
		ft_swapc(&str[cnt], &str[0]);
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_g(t_tab *tab)
{
	if (!conv_g_init(tab))
		return ;
	if (has_flag('#', tab))
		handle_trail(tab);
	if (has_flag('+', tab) || has_flag(' ', tab))
		handle_sign(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
}
