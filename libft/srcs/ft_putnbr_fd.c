/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:52:57 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:54:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
