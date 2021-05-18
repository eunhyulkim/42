/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_etoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:56:18 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*remove_zero_dot_rev(char *str)
{
	t_uint		i;

	i = ft_strlen(str);
	while (--i)
	{
		if (str[i] == '0')
			str[i] = 0;
		else if (str[i] == '.')
		{
			str[i] = 0;
			break ;
		}
		else
			break ;
	}
	return (str);
}

static char		*etoa_gets(t_ldouble n, t_uint len)
{
	t_llint		nb;
	char		*front;
	char		*back;

	nb = n;
	front = ft_lltoa(nb);
	if (n >= 0)
		back = ft_lltoa((t_llint)((n - nb + 1) * ft_pow(10, len)));
	else
		back = ft_lltoa((t_llint)((n - nb - 1) * ft_pow(10, len) * (-1)));
	back[0] = '.';
	return (ft_strmjoin(front, back));
}

static void		etoa_init(t_uint *pow, t_ldouble *n, \
int *sign, t_uint len)
{
	t_ldouble	nbf;

	*pow = 0;
	*sign = 0;
	if (*n == 0)
		return ;
	nbf = (*n < 0) ? -(*n) : *n;
	*sign = (nbf != 0 && nbf < 1) ? -1 : 1;
	while (nbf < 1.0 || nbf >= 10.0)
	{
		(*pow)++;
		nbf *= (nbf < 1.0) ? 10.0 : 0.1;
	}
	if (ft_round(nbf, len) >= 10)
	{
		nbf *= 0.1;
		*pow += (*n >= (t_ldouble)10.0) ? 1 : -1;
	}
	*n = (len <= 14) ? ft_round(nbf, len) : ft_round(nbf, len + 1);
}

static char		*etoa_suffix(int sign, t_uint pow)
{
	char		*front;
	char		*back;

	if (pow == 0)
		return (ft_strdup("e+00"));
	front = (sign == -1) ? ft_strdup("e-") : ft_strdup("e+");
	back = ft_lltoa(pow);
	if (pow < 10)
		back = ft_strmjoin(ft_strdup("0"), back);
	else
		back = ft_strdup(back);
	return (ft_strmjoin(front, back));
}

char			*ft_etoa(t_ldouble n, t_uint len, t_uint gopt)
{
	t_llint		nb;
	t_uint		pow;
	int			sign;
	char		*head;
	char		*str;

	head = (n < 0) ? ft_strdup("-") : 0;
	etoa_init(&pow, &n, &sign, len);
	if (len == 0)
	{
		nb = n;
		str = ft_strmjoin(ft_lltoa(nb), etoa_suffix(sign, pow));
		if (head)
			str = ft_strmjoin(head, str);
		return (str);
	}
	str = etoa_gets(n, len);
	if (gopt == 1)
		remove_zero_dot_rev(str);
	str = ft_strmjoin(str, etoa_suffix(sign, pow));
	if (head)
		str = ft_strmjoin(head, str);
	return (str);
}
