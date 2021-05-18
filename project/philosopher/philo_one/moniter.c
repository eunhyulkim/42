/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:05:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*moniter_heart_routine(void *sopher_arg)
{
	t_mutex		*mutex;
	t_sopher	*sopher;
	int			time_die;

	sopher = (t_sopher *)sopher_arg;
	time_die = sopher->info->time_die;
	mutex = sopher->mutex;
	while (1)
	{
		pthread_mutex_lock(&mutex->sopher_m[sopher->seat_no - 1]);
		if (!sopher->is_eating && (int)get_hungry_time(sopher) >= time_die)
		{
			print_message(sopher, TYPE_DIED);
			pthread_mutex_unlock(&mutex->sopher_m[sopher->seat_no - 1]);
			pthread_mutex_unlock(&mutex->dead_m);
			return (void *)(NULL);
		}
		pthread_mutex_unlock(&mutex->sopher_m[sopher->seat_no - 1]);
		usleep(1000);
	}
}

void	moniter_heart(t_sopher *sophers, t_info *info)
{
	t_sopher	*sopher;
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < info->numbers)
	{
		sopher = &sophers[i];
		pthread_create(&thread, NULL, &moniter_heart_routine, (void *)sopher);
		pthread_detach(thread);
		i++;
	}
}

void	*moniter_count_routine(void *sophers)
{
	t_info		*info;
	t_mutex		*mutex;
	t_sopher	*sopher;
	int			total;
	int			i;

	sopher = (t_sopher *)sophers;
	info = sopher->info;
	mutex = sopher->mutex;
	total = 0;
	while (total < info->must_eat)
	{
		i = 0;
		while (i < info->numbers)
			pthread_mutex_lock(&mutex->eat_m[i++]);
		total++;
	}
	print_message(&sopher[0], TYPE_OVER);
	pthread_mutex_unlock(&mutex->dead_m);
	return (void *)(NULL);
}

void	moniter_count(t_sopher *sophers)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &moniter_count_routine, (void *)sophers);
	pthread_detach(thread);
	return ;
}
