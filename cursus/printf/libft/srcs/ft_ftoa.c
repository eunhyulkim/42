/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/10 15:09:55 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*ftoa_gets(t_ldouble n, t_uint len)
{
	t_llint		nb;
	char		*front;
	char		*back;
	int			sign;

	sign = (n < 0) ? -1 : 1;
	nb = n;
	front = ft_lltoa(nb);
	if (sign == -1 && front[0] != '-')
		front = ft_strmjoin(ft_strdup("-"), front);
	if (n >= 0)
		back = ft_lltoa((t_llint)((n - nb + 1) * ft_pow(10, len)));
	else
		back = ft_lltoa((t_llint)((n - nb - 1) * ft_pow(10, len) * (-1)));
	back[0] = '.';
	return (ft_strmjoin(front, back));
}

static void		ftoa_init(t_ldouble *n, t_uint len)
{
	double		sign;

	sign = 0;
	if (*n == 0)
		return ;
	*n = ft_round(*n, (int)len);
}

char			*ft_ftoa(t_ldouble n, t_uint len)
{
	t_llint		nb;
	char		*str;

	ftoa_init(&n, len);
	if (len == 0)
	{
		nb = n;
		str = ft_lltoa(nb);
		if (n < 0 && str[0] != '-')
			str = ft_strmjoin(ft_strdup("-"), str);
		return (str);
	}
	str = ftoa_gets(n, len);
	return (str);
}
