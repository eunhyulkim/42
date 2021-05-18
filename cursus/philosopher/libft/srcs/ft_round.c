/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:33:21 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldouble	ft_round(t_ldouble n, int digit)
{
	t_llint			nb;
	t_ldouble		n2;
	double			sign;

	if (n == 0)
		return (n);
	sign = (n < 0) ? -0.5 : 0.5;
	n2 = (n < 0) ? -n : n;
	n2 *= ft_pow(10, digit);
	if ((nb = n2 * 10) % 10 != 5)
		return ((n * ft_pow(10, digit) + sign) / ft_pow(10, digit));
	if (n2 * 10 - (t_ldouble)nb != 0)
		return ((n * ft_pow(10, digit) + sign) / ft_pow(10, digit));
	if ((nb = n2) % 2 == 1)
		return ((n * ft_pow(10, digit) + sign) / ft_pow(10, digit));
	return (n);
}
