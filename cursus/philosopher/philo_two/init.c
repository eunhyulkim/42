/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:03:28 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 16:40:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char			*get_semname(int i, char type)
{
	char	*name;

	name = ft_strdup("/philo2_");
	if (type == "EAT"[0])
		name = ft_strmjoin(name, ft_strdup("eat"));
	else if (type == "SOPHER"[0])
		name = ft_strmjoin(name, ft_strdup("sopher"));
	name = ft_strmjoin(name, ft_itoa(i));
	return (name);
}

static void		open_multiple_sem(int i, t_semaphore *head)
{
	char	*name;

	name = 0;
	name = get_semname(i, 'E');
	sem_unlink(name);
	head->eat_s[i] = sem_open(name, O_CREAT, 0644, 1);
	free(name);
	name = get_semname(i, 'S');
	sem_unlink(name);
	head->sopher_s[i] = sem_open(name, O_CREAT, 0644, 1);
	free(name);
	sem_wait(head->eat_s[i]);
	return ;
}

int				init_semaphore(t_semaphore **sem, t_info *info)
{
	t_semaphore		*head;
	int				i;

	if (!(*sem = (t_semaphore *)ft_calloc(sizeof(t_semaphore), 1)))
		return (FALSE);
	head = *sem;
	if (!(head->eat_s = (sem_t **)ft_calloc(sizeof(sem_t *), info->numbers)))
		return (FALSE);
	if (!(head->sopher_s = (sem_t **)ft_calloc(sizeof(sem_t *), info->numbers)))
		return (FALSE);
	sem_unlink("/philo2_write");
	head->write_s = sem_open("/philo2_write", O_CREAT, 0644, 1);
	sem_unlink("/philo2_dead");
	head->dead_s = sem_open("/philo2_dead", O_CREAT, 0644, 1);
	sem_wait(head->dead_s);
	sem_unlink("/philo2_fork");
	if (info->numbers > 1)
		head->fork_s = sem_open("/philo2_fork", O_CREAT, 0644, \
		info->numbers / 2);
	i = -1;
	while (++i < info->numbers)
		open_multiple_sem(i, head);
	return (TRUE);
}

int				init_philosophers(t_sopher **sophers_ref, t_info *info, \
		t_semaphore *sem)
{
	t_sopher	*sophers;
	int			i;

	if (!(*sophers_ref = (t_sopher *)ft_calloc(sizeof(t_sopher), \
	(info->numbers))))
		return (FALSE);
	sophers = *sophers_ref;
	i = 0;
	while (i < info->numbers)
	{
		sophers[i].info = info;
		sophers[i].semaphore = sem;
		sophers[i].seat_no = i + 1;
		i++;
	}
	return (TRUE);
}
