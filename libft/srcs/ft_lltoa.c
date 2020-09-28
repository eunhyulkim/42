/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:12:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/11 19:11:23 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(t_llint n)
{
	t_llint		nb;
	int			digit;
	char		*str;

	nb = n;
	digit = (n <= 0) ? 1 : 0;
	while (nb != 0)
	{
		nb /= 10;
		digit++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (digit + 1))))
		return (0);
	str[digit--] = 0;
	nb = n;
	while (nb != 0)
	{
		str[digit] = (char)(ft_abs(nb % 10) + 48);
		nb = nb / 10;
		digit--;
	}
	str[0] = (n < 0) ? '-' : str[0];
	str[0] = (n == 0) ? '0' : str[0];
	return (str);
}
