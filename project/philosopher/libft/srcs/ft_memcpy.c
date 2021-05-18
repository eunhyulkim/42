/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 22:21:22 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:29:54 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_uchar		*uc_dst;
	t_uchar		*uc_src;
	size_t		index;

	if (!dst && !src)
		return (0);
	uc_dst = (t_uchar *)dst;
	uc_src = (t_uchar *)src;
	index = 0;
	while (index < n)
	{
		uc_dst[index] = uc_src[index];
		index++;
	}
	return (dst);
}
