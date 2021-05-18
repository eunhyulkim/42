/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_doublestr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:29:00 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:49:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_remove_doublestr(char **str, int idx)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	len = ft_len_doublestr(str);
	if (!(ret = (char **)ft_calloc(sizeof(char *), len)))
		return (0);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != idx && !(ret[j++] = ft_strdup(str[i])))
			return (0);
		i++;
	}
	ft_free_doublestr(&str);
	return (ret);
}
