/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:48:54 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 01:36:51 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		print_wstr(t_tab *tab)
{
	t_uchar		*str;
	t_uint		len;
	t_uint		i;

	i = 0;
	len = 0;
	str = (t_uchar *)tab->content;
	while (i < tab->count)
		len += tab->w_size[i++];
	if (tab->width > len && !has_flag('-', tab))
	{
		write(1, str, tab->width - len);
		str += tab->width - len;
	}
	i = 0;
	while (i < tab->count)
	{
		write(1, str, (int)tab->w_size[i]);
		str += tab->w_size[i++];
	}
	if (tab->width > len && has_flag('-', tab))
		write(1, str, tab->width - len);
	tab->count = (len > tab->width) ? len : tab->width;
	free(tab->w_size);
}

void			print_content(t_tab *tab)
{
	if (ft_isset(tab->type, "pdiuxXofge") || tab->type == '%')
		write(1, (char *)tab->content, tab->count);
	else if (tab->type == 'c' && tab->size != 'l')
		write(1, (char *)tab->content, tab->count);
	else if (tab->type == 'c' && tab->size == 'l')
		write(1, (t_uchar *)tab->content, tab->count);
	else if (tab->type == 's' && tab->size != 'l')
		write(1, (char *)tab->content, tab->count);
	else if (tab->type == 's' && tab->size == 'l' && tab->w_size != 0)
		print_wstr(tab);
	else if (tab->type == 's' && tab->size == 'l' && tab->w_size == 0)
		write(1, (t_uchar *)tab->content, tab->count);
	tab->length += tab->count;
	free(tab->content);
}
