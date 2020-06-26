/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:29:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:48:43 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uchar		*ft_ustrdup(const t_uchar *src)
{
	t_uchar	*str;
	int		i;

	if (!(str = (t_uchar *)malloc(sizeof(t_uchar) * (ft_ustrlen(src) + 1))))
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
