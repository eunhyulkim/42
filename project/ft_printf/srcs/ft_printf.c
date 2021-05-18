/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:18:16 by eunhkim           #+#    #+#             */
/*   Updated: 2020/09/24 16:09:24 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

clock_t		g_start;

static int		initialize(t_tab **tab, const char *format)
{
	if (!(*tab = (t_tab *)malloc(sizeof(t_tab) * 1)))
		return (0);
	if (!((*tab)->origin = ft_strdup((char *)format)))
		return (0);
	(*tab)->treat = (*tab)->origin;
	ft_memset((*tab)->flag, 0, sizeof((*tab)->flag));
	(*tab)->content = 0;
	(*tab)->width = 0;
	ft_memset((*tab)->sharp, 0, sizeof((*tab)->sharp));
	(*tab)->size = 0;
	(*tab)->type = 0;
	(*tab)->count = 0;
	(*tab)->length = 0;
	(*tab)->w_size = 0;
	return (1);
}

int				ft_printf(const char *format, ...)
{
	t_tab		*tab;
	int			len;

	g_start = clock();
	tab = 0;
	if (!format || !initialize(&tab, format))
	{
		write(1, "", 1);
		return (0);
	}
	va_start(tab->ap, format);
	action(tab);
	va_end(tab->ap);
	len = tab->length;
	free(tab->origin);
	free(tab);
	return (len);
}
