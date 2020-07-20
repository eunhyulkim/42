/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:03:28 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 15:41:17 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex(t_mutex **mutex, t_info *info)
{
	t_mutex		*head;
	int			i;

	if (!(*mutex = (t_mutex *)ft_calloc(sizeof(t_mutex), 1)))
		return (FALSE);
	head = *mutex;
	if (!(head->eat_m = (t_pm *)ft_calloc(sizeof(t_pm), info->numbers)))
		return (FALSE);
	if (!(head->fork_m = (t_pm *)ft_calloc(sizeof(t_pm), info->numbers)))
		return (FALSE);
	if (!(head->sopher_m = (t_pm *)ft_calloc(sizeof(t_pm), info->numbers)))
		return (FALSE);
	pthread_mutex_init(&head->write_m, NULL);
	pthread_mutex_init(&head->dead_m, NULL);
	pthread_mutex_lock(&head->dead_m);
	i = -1;
	while (++i < info->numbers)
	{
		pthread_mutex_init(&head->eat_m[i], NULL);
		pthread_mutex_lock(&head->eat_m[i]);
		pthread_mutex_init(&head->fork_m[i], NULL);
		pthread_mutex_init(&head->sopher_m[i], NULL);
	}
	return (TRUE);
}

int		init_philosophers(t_sopher **sophers_ref, t_info *info, \
		t_mutex *mutex)
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
		sophers[i].mutex = mutex;
		sophers[i].seat_no = i + 1;
		if (i % 2 == 0)
			sophers[i].first_fork = i;
		else
			sophers[i].first_fork = (i + 1) % info->numbers;
		if (i % 2 == 0)
			sophers[i].second_fork = (i + 1) % info->numbers;
		else
			sophers[i].second_fork = i;
		i++;
	}
	return (TRUE);
}
