/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:24:25 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/12 00:00:45 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*str_add(char *dst, char *src)
{
	int		i;
	int		j;

	if (!src)
		return (dst);
	if (!dst)
		return (src);
	i = ft_strlen(dst);
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	return (dst);
}

char			*ft_strsjoin(char *s1, char *s2, char *s3, char *s4)
{
	char	*str;
	int		lens;

	lens = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
	if (!(str = (char *)ft_calloc(sizeof(char), lens + 1)))
		return (0);
	str_add(str, s1);
	str_add(str, s2);
	str_add(str, s3);
	str_add(str, s4);
	return ((char *)str);
}
