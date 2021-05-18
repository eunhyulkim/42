/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:05:30 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		range_over(char *src)
{
	int		len;
	int		i;

	len = ft_strlen(src);
	if (len < 10)
		return (FALSE);
	if (len > 10)
		return (TRUE);
	i = 0;
	while (i < len)
	{
		if ("2147483647"[i] < src[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		parse(int ac, char *av[], t_info *info)
{
	int		i;
	int		nb;

	info->must_eat = 0;
	i = 1;
	nb = 0;
	while (i < ac)
	{
		if (!ft_isnumber(av[i]) || range_over(av[i]) || !(nb = ft_atoi(av[i])))
			return (0);
		if (i == 1)
			info->numbers = nb;
		else if (i == 2)
			info->time_die = nb;
		else if (i == 3)
			info->time_eat = nb * 1000;
		else if (i == 4)
			info->time_sleep = nb * 1000;
		else if (i == 5)
			info->must_eat = nb;
		i++;
	}
	return (1);
}
