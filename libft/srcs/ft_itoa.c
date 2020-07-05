/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:23:28 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(t_llint n)
{
	t_llint		nb;
	int			digit;
	char		*str;

	nb = (n < 0) ? -n : n;
	digit = (n <= 0) ? 1 : 0;
	while (nb > 0)
	{
		nb /= 10;
		digit++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (digit + 1))))
		return (0);
	str[digit--] = 0;
	nb = (n < 0) ? -n : n;
	while (nb > 0)
	{
		str[digit] = (nb % 10) + 48;
		nb = nb / 10;
		digit--;
	}
	str[0] = (n < 0) ? '-' : str[0];
	str[0] = (n == 0) ? '0' : str[0];
	return (str);
}
