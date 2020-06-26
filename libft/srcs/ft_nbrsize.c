/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:34:59 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:15:35 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrsize(int *nbr)
{
	int		cnt;

	if (!nbr)
		return (0);
	cnt = 0;
	while (nbr[cnt] != -1)
		cnt++;
	return (cnt);
}
