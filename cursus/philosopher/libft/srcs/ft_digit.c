/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:31:53 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:54:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_digit(t_llint num)
{
	int digit;

	if (num == 0)
		return (0);
	num = (num < 0) ? (-num) : num;
	digit = 0;
	while (num > 0)
	{
		num /= 10;
		digit++;
	}
	return (digit);
}
