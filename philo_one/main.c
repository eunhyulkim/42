/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:04:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:09:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		philosophy_one(t_info *info)
{
	t_mutex		*mutex;
	t_sopher	*sophers;

	mutex = 0;
	sophers = 0;
	if (!init_mutex(&mutex, info))
		return (free_mutex(mutex));
	if (!init_philosophers(&sophers, info, mutex))
		return (free_mutex(mutex));
	log_init_philosophers(info, sophers);
	set_start_time(info);
	if (info->must_eat)
		moniter_count(sophers);
	moniter_heart(sophers, info);
	simulation(sophers);
	safe_escape(info, mutex, sophers);
	return (TRUE);
}

int		main(int ac, char *av[])
{
	t_info	info;

	if ((g_fd = open("../log/log.txt", O_RDWR | O_TRUNC | O_CREAT, 0644)) < 0)
		return (1);
	if ((g_rfd = open("../log/result.txt", O_RDWR | O_TRUNC | O_CREAT, 0644)) < 0)
		return (1);
	if (ac < 5 || ac > 6)
		ft_error("argument count must be between 5 and 6");
	if (!parse(ac, av, &info))
		ft_error("argument value must be over 0 integer");
	dprintf(g_fd, "[ARG PARSE]\n[numbers: %d][time_die: %d]\
	[time_eat: %d][time_sleep: %d][must_eat: %d]\n\n", \
	info.numbers, info.time_die, info.time_eat, info.time_sleep, info.must_eat);
	if (!philosophy_one(&info))
		ft_error("malloc failed and not started");
	close(g_fd);
	close(g_rfd);
	return (0);
}
