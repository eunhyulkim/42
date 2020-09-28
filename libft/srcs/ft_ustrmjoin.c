/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrmjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:24:25 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:58:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uchar	*ft_ustrmjoin(t_uchar *s1, t_uchar *s2)
{
	t_uchar	*str;
	int		lens;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	lens = ft_ustrlen(s1) + ft_ustrlen(s2);
	if (!(str = (t_uchar *)malloc(sizeof(t_uchar) * (lens + 1))))
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		str[i++] = s2[j];
	str[i] = 0;
	free(s1);
	free(s2);
	return (str);
}
