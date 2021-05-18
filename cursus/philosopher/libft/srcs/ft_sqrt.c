/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:09:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:57:42 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	t_llint		r;
	int			c;
	t_llint		nbr;

	nbr = nb;
	if (nbr < 1)
		return (0);
	c = 1;
	r = (nbr < 1000000) ? 1000 : 35000;
	while (c)
	{
		if (r * r == nbr)
			c = 0;
		else if (nbr > (r * r) && nbr < (r + 1) * (r + 1))
		{
			c = 0;
		}
		if (c)
			r = ((nbr / r) + r) / 2;
	}
	return ((int)r);
}
