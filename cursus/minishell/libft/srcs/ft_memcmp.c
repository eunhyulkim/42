/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:18:19 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:30:57 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_uchar		*uc_s1;
	t_uchar		*uc_s2;
	size_t		i;

	uc_s1 = (t_uchar *)s1;
	uc_s2 = (t_uchar *)s2;
	i = 0;
	while (i < n)
	{
		if (uc_s1[i] != uc_s2[i])
			return ((int)uc_s1[i] - (int)uc_s2[i]);
		i++;
	}
	return (0);
}
