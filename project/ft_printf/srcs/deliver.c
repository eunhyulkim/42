/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deliver.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:48:54 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:34:22 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		deliver_bonus(char c, t_tab *tab)
{
	if (c == 'f')
		conversion_f(tab);
	else if (c == 'e')
		conversion_e(tab);
	else if (c == 'g')
		conversion_g(tab);
	else if (c == 'n')
		conversion_n(tab);
	else if (c == 'o')
		conversion_o(tab);
}

void			deliver(t_tab *tab)
{
	char		c;

	if ((c = (char)(tab->type)) == 'c')
		conversion_c(tab);
	else if (c == 's')
		conversion_s(tab);
	else if (c == 'p')
		conversion_p(tab);
	else if (c == 'd' || c == 'i')
		conversion_di(tab);
	else if (c == 'u')
		conversion_u(tab);
	else if (c == 'x' || c == 'X')
		conversion_xx(tab);
	else if (c == '%')
		conversion_oo(tab);
	else
		deliver_bonus(c, tab);
}
