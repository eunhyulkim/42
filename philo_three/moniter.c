/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:13:20 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*moniter_heart_routine(void *sopher_arg)
{
	t_semaphore	*sem;
	t_sopher	*sopher;
	int			time_die;

	sopher = (t_sopher *)sopher_arg;
	time_die = sopher->info->time_die;
	sem = sopher->semaphore;
	while (1)
	{
		sem_wait(sem->sopher_s[sopher->seat_no - 1]);
		dprintf(g_rfd, "hungry_time: %d\n", (int)get_hungry_time(sopher));
		if (!sopher->is_eating && (int)get_hungry_time(sopher) >= time_die)
		{
			print_message(sopher, TYPE_DIED);
			sem_post(sem->sopher_s[sopher->seat_no - 1]);
			sem_post(sem->dead_s);
			return (void *)(NULL);
		}
		sem_post(sem->sopher_s[sopher->seat_no - 1]);
		usleep(1000);
	}
	return (void *)(NULL);
}

void	*moniter_count_routine(void *sophers)
{
	t_info		*info;
	t_semaphore	*sem;
	t_sopher	*sopher;
	int			total;
	int			i;

	sopher = (t_sopher *)sophers;
	info = sopher->info;
	sem = sopher->semaphore;
	total = 0;
	while (total < info->must_eat)
	{
		i = 0;
		while (i < info->numbers)
			sem_wait(sem->eat_s[i++]);
		total++;
	}
	print_message(&sopher[0], TYPE_OVER);
	sem_post(sem->dead_s);
	return (void *)(NULL);
}

void	moniter_count(t_sopher *sophers)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &moniter_count_routine, (void *)sophers);
	pthread_detach(thread);
	return ;
}
