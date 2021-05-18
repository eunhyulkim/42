/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:39:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:33:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	check_size(t_tab *tab)
{
	char	*str;

	str = tab->treat;
	if (*str == 'L')
	{
		tab->size = 'L';
		tab->treat++;
		return ;
	}
	if (!ft_isset(*str, "hlL"))
		return ;
	else if (*str == 'h' && *(str + 1) == 'h')
		tab->size = 'H';
	else if (*str == 'h' && *(str + 1) != 'h')
		tab->size = 'h';
	else if (*str == 'l' && *(str + 1) != 'l')
		tab->size = 'l';
	else if (*str == 'l' && *(str + 1) == 'l')
		tab->size = 'L';
	if (tab->size == 'H' || tab->size == 'L')
		str += 2;
	else if (tab->size != 0)
		str += 1;
	tab->treat = str;
}
