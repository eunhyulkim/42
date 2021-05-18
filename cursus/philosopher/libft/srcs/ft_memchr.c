/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:02:57 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:30:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_uchar		*str;
	t_uint		i;

	str = (t_uchar *)s;
	i = 0;
	while (i < n && (str[i] != (t_uchar)c))
		i++;
	if (i == n)
		return (0);
	return ((void *)(&str[i]));
}
