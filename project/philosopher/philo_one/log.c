/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:06:54 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 11:06:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	log_init_philosophers(t_info *info, t_sopher *sophers)
{
	int			i;

	i = 0;
	dprintf(g_fd, "[PHILOSOPHER INIT]\n");
	while (i < info->numbers)
	{
		dprintf(g_fd, "[%dth]", sophers[i].seat_no);
		dprintf(g_fd, "[first_fork: %d]", sophers[i].first_fork);
		dprintf(g_fd, "[second_fork: %d]\n", sophers[i].second_fork);
		i++;
	}
	dprintf(g_fd, "\n");
}
