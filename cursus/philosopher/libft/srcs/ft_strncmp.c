/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:36:06 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:39:06 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	t_uchar		*s3;
	t_uchar		*s4;

	s3 = (t_uchar *)s1;
	s4 = (t_uchar *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s3[i] == s4[i] && s3[i] != '\0' && s4[i] != '\0')
		i++;
	return ((int)s3[i] - (int)s4[i]);
}
