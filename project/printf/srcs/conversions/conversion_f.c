/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:26:47 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 04:56:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		conv_f_init(t_tab *tab)
{
	double		d;
	t_ldouble	ld;
	t_uint		len;

	len = has_sharp(tab) ? get_sharp(tab) : 6;
	if (tab->size == 'L')
		ld = va_arg(tab->ap, t_ldouble);
	else
		d = va_arg(tab->ap, double);
	tab->content = (tab->size == 'L') ? ft_ftoa(ld, len) : ft_ftoa(d, len);
	if (!tab->content)
		return (0);
	if (((char *)tab->content)[0] == '-')
		unuse_flag(" ", tab);
	return (1);
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

void			conversion_f(t_tab *tab)
{
	if (!conv_f_init(tab))
		return ;
	if (has_flag('#', tab) && has_sharp(tab) && get_sharp(tab) == 0)
		tab->content = ft_strmjoin((char *)tab->content, ft_strdup("."));
	if (has_flag('+', tab) || has_flag(' ', tab))
		handle_sign(tab);
	if (tab->width > ft_strlen((char *)tab->content))
		handle_width(tab);
	tab->count = ft_strlen((char *)tab->content);
}
