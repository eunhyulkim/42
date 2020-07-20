/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:59:28 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/20 17:42:40 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr_fd(t_llint n, int fd)
{
	t_llint	nb;

	if (fd < 0)
		return ;
	nb = (n < 0) ? (n * -1) : n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (nb >= 10)
		ft_putnbr_fd((nb / 10), fd);
	ft_putchar_fd((char)(nb % 10) + 48, fd);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
	return ;
}
