/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:52 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:09:27 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	take_forks(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
	{
		print_message(sopher, TYPE_THINK);
		usleep(sopher->info->time_die * 2000);
	}
	else
	{
		sem_wait(sopher->semaphore->fork_s);
		print_message(sopher, TYPE_FORKUP);
		print_message(sopher, TYPE_FORKUP);
	}
}

void	clean_forks(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
		return ;
	sem_post(sopher->semaphore->fork_s);
	print_message(sopher, TYPE_SLEEP);
	usleep(sopher->info->time_sleep);
	return ;
}

void	eat(t_sopher *sopher)
{
	if (sopher->info->numbers == 1)
		return ;
	sem_wait(sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sopher->is_eating = TRUE;
	print_message(sopher, TYPE_EAT);
	usleep(sopher->info->time_eat);
	sopher->count_eat += 1;
	sopher->last_time = get_time(sopher);
	sopher->is_eating = FALSE;
	sem_post(sopher->semaphore->sopher_s[sopher->seat_no - 1]);
	sem_post(sopher->semaphore->eat_s[sopher->seat_no - 1]);
	return ;
}

void	dup_semaphore(t_sopher *sopher)
{
	t_semaphore	*sem;
	char		*name;
	int			i;

	sem = sopher->semaphore;
	sem->write_s = sem_open(NAME_WRITE, O_CREAT, 0644, 1);
	sem->dead_s = sem_open(NAME_DIED, O_CREAT, 0644, 1);
	sem->fork_s = sem_open(NAME_FORK, O_CREAT, 0644, 1);
	name = 0;
	i = sopher->seat_no;
	name = get_semname(i, 'E');
	sem->eat_s[i] = sem_open(name, O_CREAT, 0644, 1);
	free(name);
	name = get_semname(i, 'S');
	sem->sopher_s[i] = sem_open(name, O_CREAT, 0644, 1);
	free(name);
}

void	*live(void *sopher_void)
{
	t_sopher *sopher;

	sopher = (t_sopher *)sopher_void;
	while (1)
	{
		// dup_semaphore(sopher);
		take_forks(sopher);
		eat(sopher);
		clean_forks(sopher);
		if (sopher->info->numbers != 1)
			print_message(sopher, TYPE_THINK);
	}
	return ((void *)(NULL));
}

void	simulation(t_sopher *sophers)
{
	int			i;
	int			numbers;
	pid_t		tid;
	pthread_t	thread;

	numbers = sophers->info->numbers;
	i = -1;
	while (++i < numbers)
	{
		dprintf(g_fd, "%d sopher's simulation start\n", sophers[i].seat_no);
		tid = fork();
		if (tid > 0)
		{
			pthread_create(&thread, NULL, &moniter_heart_routine, \
			(void *)&sophers[i]);
			pthread_detach(thread);
			live((void *)&sophers[i]);
			exit(EXIT_SUCCESS);
		}
		usleep(100);
	}
	return ;
}
