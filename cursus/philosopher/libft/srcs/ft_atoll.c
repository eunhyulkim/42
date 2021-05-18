/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:48:17 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:54:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llint	ft_atoll(char *str)
{
	t_llint	sign;
	t_llint	value;

	if (!str || !(*str))
		return (0);
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
	return (sign * value);
}
