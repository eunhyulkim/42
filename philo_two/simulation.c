/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 17:21:44 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		take_forks(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
	{
		print_message(sopher, TYPE_THINK);
		usleep(sopher->info->time_die * 2000);
	}
	else
	{
		sem_wait(sopher->semaphore->fork_s);
		if (!print_message(sopher, TYPE_FORKUP))
			return (0);
		if (!print_message(sopher, TYPE_FORKUP))
			return (0);
	}
	return (1);
}

int		clean_forks(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
		return (1);
	sem_post(sopher->semaphore->fork_s);
	if (!print_message(sopher, TYPE_SLEEP))
		return (0);
	usleep(sopher->info->time_sleep);
	return (1);
}

int		eat(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
		return (1);
	sem_wait(sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sopher->is_eating = TRUE;
	if (!print_message(sopher, TYPE_EAT))
		return (0);
	usleep(sopher->info->time_eat);
	sopher->count_eat += 1;
	sopher->last_time = get_time(sopher);
	sopher->is_eating = FALSE;
	sem_post(sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sem_post(sopher->semaphore->eat_s[sopher->seat_no - 1]);
	return (1);
}

void	*live(void *sopher)
{
	while (1)
	{
		if (!take_forks(sopher))
			break ;
		if (!eat(sopher))
			break ;
		if (!clean_forks(sopher))
			break ;
		if (!print_message(sopher, TYPE_THINK))
			break ;
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
