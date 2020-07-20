/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:03:28 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:42:13 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_unlink(NAME_WRITE);
	head->write_s = sem_open(NAME_WRITE, O_CREAT, 0644, 1);
	sem_unlink(NAME_DWRITE);
	head->dwrite_s = sem_open(NAME_DWRITE, O_CREAT, 0644, 1);
	sem_unlink(NAME_DIED);
	head->dead_s = sem_open(NAME_DIED, O_CREAT, 0644, 1);
	sem_wait(head->dead_s);
	sem_unlink(NAME_FORK);
	if (info->numbers > 1)
		head->fork_s = sem_open(NAME_FORK, O_CREAT, 0644, \
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
