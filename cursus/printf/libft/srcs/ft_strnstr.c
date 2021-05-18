/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 00:35:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:39:59 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s2[0] && len == 0)
		return ((char *)s1);
	while (i < len)
	{
		j = 0;
		while (s1[i] == s2[0] && s1[i + j] && s2[j] && s1[i + j] == s2[j])
			j++;
		if (!(s2[j]) && (i + j <= len))
			return ((char *)&s1[i]);
		i++;
	}
	return (0);
}
