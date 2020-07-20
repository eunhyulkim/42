/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trans_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:58:38 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:40:45 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trans_base(t_ullint nb, char *base)
{
	char		*rstr;
	t_ullint	nbr;
	t_ullint	base_len;
	t_uint		i;

	base_len = (t_ullint)ft_strlen(base);
	nbr = nb;
	i = (nbr == 0) ? 1 : 0;
	while (nbr > 0)
	{
		nbr = nbr / base_len;
		i++;
	}
	rstr = (char *)malloc(sizeof(char) * (i + 1));
	rstr[i] = 0;
	rstr[0] = (nb == 0) ? '0' : rstr[0];
	while (i--)
	{
		rstr[i] = base[nb % base_len];
		nb = nb / base_len;
	}
	return (rstr);
}
