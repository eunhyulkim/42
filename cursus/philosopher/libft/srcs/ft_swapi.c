/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:08:48 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:58:34 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_swapi(int *nb1, int *nb2)
{
	int temp;

	if (!nb1 || !nb2)
		return (0);
	temp = *nb1;
	*nb1 = *nb2;
	*nb2 = temp;
	return (1);
}