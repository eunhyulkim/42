/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:31:53 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:32:46 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llint	ft_pow(t_llint num, int pow)
{
	t_llint		nb;

	if (pow == 0)
		return (1);
	nb = num;
	while (--pow)
		num *= nb;
	return (num);
}
