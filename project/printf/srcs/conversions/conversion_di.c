/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:26:47 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/10 01:28:51 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		conv_di_init(t_tab *tab)
{
	tab->content = ft_lltoa(conv_arg_ll(tab));
	if (!tab->content)
		return (0);
	if (((char *)tab->content)[0] == '-')
		unuse_flag(" ", tab);
	if (has_sharp(tab))
		unuse_flag("0", tab);
	unuse_flag("#", tab);
	return (1);
}

static void		handle_sharp(t_tab *tab)
{
	char		*str;
	int			digit;
	int			index;
	int			cnt;

	str = (char *)tab->content;
	if (!get_sharp(tab) && ft_iszero(str))
		str = ft_strfreedup(str, "");
	digit = (str[0] == '-') ? ft_strlen(str) - 1 : ft_strlen(str);
	if ((cnt = (int)get_sharp(tab) - digit) <= 0 || !digit)
	{
		tab->content = str;
		return ;
	}
	index = cnt;
	while (cnt--)
		str = ft_strmjoin(ft_strdup("0"), str);
	if (str[index] == '-')
		ft_swapc(&str[0], &str[index]);
	tab->content = str;
	return ;
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

void			conversion_di(t_tab *tab)
{
	if (!conv_di_init(tab))
		return ;
	if (has_sharp(tab))
		handle_sharp(tab);
	if (has_flag('+', tab) || has_flag(' ', tab))
		handle_sign(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
	return ;
}
