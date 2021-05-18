/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:59:48 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 10:59:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_isnumber(char *str)
{
	if (!str || !(*str))
		return (0);
	while (*str && *str >= 48 && *str <= 57)
		str++;
	return (*str == '\0');
}

int		ft_isset(int c, char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_isnum(t_llint c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		ft_atoi(char *str)
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
	return ((int)(sign * value));
}
