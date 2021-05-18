/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:39:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:33:28 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	check_width(t_tab *tab)
{
	char	*str;
	int		width;

	str = tab->treat;
	if (*str == '*')
	{
		if ((width = va_arg(tab->ap, int)) < 0)
		{
			put_flag('-', tab);
			unuse_flag("0", tab);
		}
		tab->width = ft_abs(width);
		str++;
	}
	else if (ft_isnum(*str))
		tab->width = (t_uint)ft_moveatoll(&str);
	tab->treat = str;
}
