/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:59:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 12:27:07 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
	close(g_fd);
	close(g_rfd);
	exit(EXIT_FAILURE);
	return ;
}

int		free_semaphore(t_semaphore *sem)
{
	if (!sem)
		return (FALSE);
	if (sem->eat_m)
		free(sem->eat_m);
	if (sem->sopher_m)
		free(sem->sopher_m);
	free(sem);
	return (FALSE);
}

void	close_and_unlink_semaphore(t_info *info, t_semaphore *sem)
{
	int		i;

	sem_close(&sem->write_s);
	sem_unlink(&sem->write_s);
	sem_close(&sem->dead_s);
	sem_unlink(&sem->dead_s);
	sem_close(&sem->fork_s);
	sem_unlink(&sem->fork_s);
	i = 0;
	while (i < info->numbers)
	{
		sem_close(&sem->eat_s[i]);
		sem_unlink(&sem->eat_s[i]);
		sem_close(&sem->sopher_s[i]);
		sem_unlink(&sem->sopher_s[i]);
		i++;
	}
	return ;
}

void	safe_escape(t_info *info, t_semaphore *sem, t_sopher *sophers)
{
	sem_wait(&sem->dead_s);
	sem_post(&sem->dead_s);
	close_and_unlink_semaphore(info, sem);
	free_semaphotre(sem);
	free(sophers);
	return ;
}
