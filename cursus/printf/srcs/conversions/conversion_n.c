/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:35:58 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 04:10:53 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		conversion_n(t_tab *tab)
{
	t_sint	*nbs;
	int		*nb;
	t_lint	*nbl;

	tab->width = 0;
	ft_memset(tab->sharp, 0, sizeof(tab->sharp));
	unuse_flag(" +0-#", tab);
	if (tab->size == 'h')
	{
		nbs = va_arg(tab->ap, t_sint *);
		*nbs = tab->length;
	}
	else if (tab->size == 'l')
	{
		nbl = va_arg(tab->ap, t_lint *);
		*nbl = tab->length;
	}
	else if (tab->size == 0)
	{
		nb = va_arg(tab->ap, int *);
		*nb = tab->length;
	}
}
