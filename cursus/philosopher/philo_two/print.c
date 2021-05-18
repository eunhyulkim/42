/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:05:32 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 17:01:46 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char	*get_message(int message_type)
{
	if (message_type == TYPE_OVER)
		return ("The set maximum times of eat has been completed");
	else if (message_type == TYPE_FORKUP)
		return ("has taken a fork");
	else if (message_type == TYPE_EAT)
		return ("is eating");
	else if (message_type == TYPE_SLEEP)
		return ("is sleeping");
	else if (message_type == TYPE_THINK)
		return ("is thinking");
	else if (message_type == TYPE_DIED)
		return ("is died");
	return (0);
}

int		print_message(t_sopher *sopher, int message_type)
{
	static int	done;
	int			res;

	res = 0;
	if (!done)
	{
		res = 1;
		sem_wait(sopher->semaphore->write_s);
		ft_putnbr_fd(get_time(sopher), STDIN);
		ft_putchar_fd(' ', STDIN);
		if (message_type == TYPE_OVER || message_type == TYPE_DIED)
			done = TRUE;
		if (message_type == TYPE_OVER)
			return (ft_putendl_fd(get_message(message_type), STDIN));
		ft_putnbr_fd(sopher->seat_no, STDIN);
		ft_putchar_fd(' ', STDIN);
		ft_putendl_fd(get_message(message_type), STDIN);
		if (message_type == TYPE_DIED)
			ft_putendl_fd("One philosopher died and eat was stopped", STDIN);
		sem_post(sopher->semaphore->write_s);
	}
	return (res);
}
