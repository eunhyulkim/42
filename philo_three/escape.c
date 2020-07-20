/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:59:07 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:36:35 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	if (sem->eat_s)
		free(sem->eat_s);
	if (sem->sopher_s)
		free(sem->sopher_s);
	free(sem);
	return (FALSE);
}

void	close_and_unlink_semaphore(t_info *info, t_semaphore *sem)
{
	int		i;
	char	*name;

	name = 0;
	(void)sem;
	sem_unlink("/philo2_write");
	sem_unlink("/philo2_dead");
	sem_unlink("/philo2_fork");
	i = 0;
	while (i < info->numbers)
	{
		name = get_semname(i, 'E');
		sem_unlink(name);
		free(name);
		name = get_semname(i, 'S');
		sem_unlink(name);
		free(name);
		i++;
	}
	dprintf(g_fd, "[safe_secape]close_and_unlink_semaphore_end\n");
	return ;
}

void	safe_escape(t_info *info, t_semaphore *sem, t_sopher *sophers)
{
	dprintf(g_fd, "[safe_secape]safe_escpae function start\n");
	sem_wait(sem->dead_s);
	sem_post(sem->dead_s);
	dprintf(g_fd, "[safe_secape]check someone's death, %llu\n", get_time(&sophers[0]));
	dprintf(g_fd, "[safe_secape]dead_s is wait and post success\n");
	close_and_unlink_semaphore(info, sem);
	dprintf(g_fd, "[safe_secape]close_and_unlink_semaphore success\n");
	free_semaphore(sem);
	dprintf(g_fd, "[safe_secape]free_semaphore success\n");
	free(sophers);
	dprintf(g_fd, "[safe_secape]safe_escpae function end\n");
	return ;
}
