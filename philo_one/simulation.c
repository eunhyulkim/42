/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:05:53 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_forks(t_sopher *sopher)
{
	pthread_mutex_lock(&sopher->mutex->fork_m[sopher->first_fork]);
	print_message(sopher, TYPE_FORKUP);
	pthread_mutex_lock(&sopher->mutex->fork_m[sopher->second_fork]);
	print_message(sopher, TYPE_FORKUP);
}

void	clean_forks(t_sopher *sopher)
{
	pthread_mutex_unlock(&sopher->mutex->fork_m[sopher->first_fork]);
	pthread_mutex_unlock(&sopher->mutex->fork_m[sopher->second_fork]);
	print_message(sopher, TYPE_SLEEP);
	usleep(sopher->info->time_sleep);
}

void	eat(t_sopher *sopher)
{
	pthread_mutex_lock(&sopher->mutex->sopher_m[sopher->seat_no - 1]);
	sopher->is_eating = TRUE;
	print_message(sopher, TYPE_EAT);
	usleep(sopher->info->time_eat);
	sopher->count_eat += 1;
	sopher->last_time = get_time(sopher);
	sopher->is_eating = FALSE;
	pthread_mutex_unlock(&sopher->mutex->sopher_m[sopher->seat_no - 1]);
	pthread_mutex_unlock(&sopher->mutex->eat_m[sopher->seat_no - 1]);
}

void	*live(void *sopher)
{
	while (1)
	{
		take_forks(sopher);
		eat(sopher);
		clean_forks(sopher);
		print_message(sopher, TYPE_THINK);
	}
	return ((void *)(NULL));
}

void	simulation(t_sopher *sophers)
{
	int			i;
	int			numbers;
	pthread_t	thread;

	numbers = sophers->info->numbers;
	i = -1;
	while (++i < numbers)
	{
		dprintf(g_fd, "%d sopher's simulation start\n", sophers[i].seat_no);
		pthread_create(&thread, NULL, &live, (void *)&sophers[i]);
		pthread_detach(thread);
		usleep(100);
	}
	return ;
}
