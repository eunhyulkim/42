/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 22:50:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:30:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_uchar		*uc_dst;
	t_uchar		*uc_src;
	size_t		i;

	uc_dst = (t_uchar *)dst;
	uc_src = (t_uchar *)src;
	i = 0;
	while (i < n)
	{
		uc_dst[i] = uc_src[i];
		if (uc_src[i] == (t_uchar)c)
			return ((void *)(dst + i + 1));
		i++;
	}
	return (0);
}
