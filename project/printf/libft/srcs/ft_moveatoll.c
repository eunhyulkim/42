/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moveatoll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:48:17 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:31:19 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llint		ft_moveatoll(char **straddr)
{
	char		*str;
	t_llint		sign;
	t_llint		value;

	if (!straddr || !(*straddr))
		return (0);
	str = *straddr;
	sign = (*str == '-') ? -1 : 1;
	str += ft_isset(*str, "-+") ? 1 : 0;
	value = 0;
	if (!(*str) || !ft_isnum(*str))
		return (0);
	while (*str && ft_isnum(*str))
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	*straddr = str;
	return (sign * value);
}
