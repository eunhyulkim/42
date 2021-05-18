/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinitialize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 10:55:41 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:37:09 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	reinitialize(t_tab *tab)
{
	ft_memset(tab->flag, 0, sizeof(tab->flag));
	tab->content = 0;
	tab->width = 0;
	ft_memset(tab->sharp, 0, sizeof(tab->sharp));
	tab->size = 0;
	tab->type = 0;
	tab->count = 0;
	tab->w_size = 0;
}
