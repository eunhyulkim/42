/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:47:01 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:47:58 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	ret;
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	j = ft_strlen(dest);
	ret = (j > dstsize) ? (dstsize + ft_strlen(src)) : (j + ft_strlen(src));
	i = 0;
	while (src[i] && j < dstsize - 1)
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (ret);
}
