/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:06:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:06:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		set_start_time(t_info *info)
{
	int				i;
	int				cnt;
	struct timeval	tv;

	i = 0;
	cnt = info->numbers;
	dprintf(g_fd, "[START TIME]\n");
	gettimeofday(&tv, NULL);
	while (i < cnt)
	{
		info->start_sec = tv.tv_sec;
		info->start_usec = tv.tv_usec;
		i++;
	}
	dprintf(g_fd, "[%ld sec][%ld usec]\n\n", info->start_sec, info->start_usec);
	return ;
}

uint64_t	get_time(t_sopher *sopher)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - sopher->info->start_sec;
	usec = now.tv_usec - sopher->info->start_usec;
	return ((sec * (uint64_t)1000) + (usec / 1000));
}

uint64_t	get_hungry_time(t_sopher *sopher)
{
	return (get_time(sopher) - sopher->last_time);
}
