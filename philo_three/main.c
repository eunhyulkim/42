/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:04:39 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:07:51 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		philosophy_three(t_info *info)
{
	t_semaphore	*sem;
	t_sopher	*sophers;

	sem = 0;
	sophers = 0;
	dprintf(g_fd, "[philosophy]philosophy_two start\n");
	if (!init_semaphore(&sem, info))
		return (free_semaphore(sem));
	dprintf(g_fd, "[philosophy]init_semaphores passed\n");
	if (!init_philosophers(&sophers, info, sem))
		return (free_semaphore(sem));
	dprintf(g_fd, "[philosophy]init_philosophers passed\n");
	set_start_time(info);
	dprintf(g_fd, "[philosophy]set_start_time passed\n");
	if (info->must_eat)
		moniter_count(sophers);
	dprintf(g_fd, "[philosophy]moniter_count passed\n");
	simulation(sophers);
	dprintf(g_fd, "[philosophy]simulation passed\n");
	safe_escape(info, sem, sophers);
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
	if (!philosophy_three(&info))
		ft_error("malloc or semaphore failed and not started");
	close(g_fd);
	close(g_rfd);
	return (0);
}
