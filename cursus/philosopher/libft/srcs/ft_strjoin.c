/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:24:25 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:53:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uchar	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lens;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	lens = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (lens + 1))))
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		str[i++] = s2[j];
	str[i] = 0;
	return ((t_uchar *)str);
}
