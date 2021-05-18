/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 02:04:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/11 21:21:38 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_ullint		conv_arg_ull(t_tab *tab)
{
	t_ullint	number;

	number = 0;
	if (tab->size == 0 || ft_isset(tab->size, "hH"))
		number = va_arg(tab->ap, unsigned int);
	else if (tab->size == 'l')
		number = va_arg(tab->ap, unsigned long int);
	else if (tab->size == 'L')
		number = va_arg(tab->ap, unsigned long long int);
	else
		return (0);
	if (tab->size == 'H')
		number = (unsigned char)number;
	else if (tab->size == 'h')
		number = (unsigned short int)number;
	else if (tab->size == 0)
		number = (unsigned int)number;
	else if (tab->size == 'l')
		number = (unsigned long int)number;
	return (number);
}

t_llint			conv_arg_ll(t_tab *tab)
{
	t_llint		number;

	number = 0;
	if (tab->size == 0 || ft_isset(tab->size, "hH"))
		number = va_arg(tab->ap, int);
	else if (tab->size == 'l')
		number = va_arg(tab->ap, long int);
	else if (tab->size == 'L')
		number = va_arg(tab->ap, long long int);
	else
		return (0);
	if (tab->size == 'H')
		number = (char)number;
	else if (tab->size == 'h')
		number = (short int)number;
	else if (tab->size == 0)
		number = (int)number;
	else if (tab->size == 'l')
		number = (long int)number;
	return (number);
}
