/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 12:32:22 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	take_forks(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
		usleep(sopher->info->time_die * 2);
	sem_wait(&sopher->semaphore->fork_s);
	print_message(sopher, TYPE_FORKUP);
	print_message(sopher, TYPE_FORKUP);
}

void	clean_forks(t_sopher *sopher)
{
	sem_post(&sopher->semaphore->fork_s);
	print_message(sopher, TYPE_SLEEP);
	usleep(sopher->info->time_sleep);
}

void	eat(t_sopher *sopher)
{
	sem_wait(&sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sopher->is_eating = TRUE;
	print_message(sopher, TYPE_EAT);
	usleep(sopher->info->time_eat);
	sopher->count_eat += 1;
	sopher->last_time = get_time(sopher);
	sopher->is_eating = FALSE;
	sem_post(&sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sem_post(&sopher->semaphore->eat_s[sopher->seat_no - 1]);
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
