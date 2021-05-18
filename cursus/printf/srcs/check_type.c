/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:39:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:33:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		check_type(t_tab *tab)
{
	char	c;

	c = *(tab->treat);
	if (ft_isset(c, "cspdiuxXnfgeo") || c == '%')
		tab->type = c;
	else
		return (0);
	return (1);
}
