/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 08:52:21 by fremoor           #+#    #+#             */
/*   Updated: 2020/07/10 02:11:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mstrjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	ft_free(s1);
	ft_free(s2);
	return (str);
}
