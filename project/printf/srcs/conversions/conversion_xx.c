/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_xx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:26:47 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 05:09:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		conv_xx_init(t_tab *tab, char **base)
{
	if (tab->type == 'x')
		*base = ft_strdup("0123456789abcdef");
	else
		*base = ft_strdup("0123456789ABCDEF");
	tab->content = ft_trans_base(conv_arg_ull(tab), *base);
	if (!tab->content)
		return (0);
	unuse_flag(" +", tab);
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
	digit = ft_strlen(str);
	if ((cnt = (int)get_sharp(tab) - digit) <= 0 || !digit)
	{
		tab->content = str;
		return ;
	}
	index = cnt;
	while (cnt--)
		str = ft_strmjoin(ft_strdup("0"), str);
	tab->content = str;
	return ;
}

static void		handle_base(t_tab *tab)
{
	char		*str;

	str = (char *)tab->content;
	if (ft_iszero(str) || !ft_strlen(str))
		return ;
	if (tab->type == 'x')
		str = ft_strmjoin(ft_strdup("0x"), str);
	else if (tab->type == 'X')
		str = ft_strmjoin(ft_strdup("0X"), str);
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
	if (has_flag('0', tab) && ft_isset(str[cnt + 1], "xX"))
		ft_swapc(&str[cnt + 1], &str[1]);
	tab->count = tab->width;
	tab->content = str;
	return ;
}

void			conversion_xx(t_tab *tab)
{
	char		*base;

	if (!conv_xx_init(tab, &base))
		return ;
	if (has_sharp(tab))
	{
		unuse_flag("0", tab);
		handle_sharp(tab);
	}
	if (has_flag('#', tab))
		handle_base(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
	free(base);
}
