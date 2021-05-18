/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 00:37:59 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:30:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	action(t_tab *tab)
{
	while (*(tab->treat))
	{
		if (*(tab->treat) != '%')
		{
			ft_putchar_fd(*(tab->treat), 1);
			tab->length++;
		}
		else
		{
			tab->treat++;
			if (!arrange(tab))
				return ;
		}
		if (*tab->treat != 0)
			tab->treat++;
	}
}
