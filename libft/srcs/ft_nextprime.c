/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextprime_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:13:56 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:15:24 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nextprime(int nbr)
{
	int		i;
	int		r;
	int		max;

	if (nbr <= 2)
		return (2);
	i = 2;
	max = ft_sqrt(nbr);
	while (i <= max)
	{
		if (nbr % i == 0)
		{
			nbr += 1;
			i = 2;
			max = ft_sqrt(nbr);
		}
		else
			i++;
	}
	r = nbr;
	return (r);
}
