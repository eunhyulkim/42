/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:59:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 10:59:07 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
	close(g_fd);
	close(g_rfd);
	exit(EXIT_FAILURE);
	return ;
}

int		free_mutex(t_mutex *mutex)
{
	if (!mutex)
		return (FALSE);
	if (mutex->eat_m)
		free(mutex->eat_m);
	if (mutex->fork_m)
		free(mutex->fork_m);
	if (mutex->sopher_m)
		free(mutex->sopher_m);
	free(mutex);
	return (FALSE);
}

void	destroy_mutex(t_info *info, t_mutex *mutex)
{
	int		i;

	pthread_mutex_destroy(&mutex->write_m);
	pthread_mutex_destroy(&mutex->dead_m);
	i = 0;
	while (i < info->numbers)
	{
		pthread_mutex_destroy(&mutex->eat_m[i]);
		pthread_mutex_destroy(&mutex->fork_m[i]);
		pthread_mutex_destroy(&mutex->sopher_m[i]);
		i++;
	}
	return ;
}

void	safe_escape(t_info *info, t_mutex *mutex, \
t_sopher *sophers)
{
	pthread_mutex_lock(&mutex->dead_m);
	pthread_mutex_unlock(&mutex->dead_m);
	destroy_mutex(info, mutex);
	free_mutex(mutex);
	free(sophers);
	return ;
}
