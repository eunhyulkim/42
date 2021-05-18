/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_doublestr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:45:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:38:50 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_realloc_doublestr(char ***strs_ref, char *item)
{
	char	**ret;
	char	**strs;
	int		len;

	strs = *strs_ref;
	if (!item)
		return (strs);
	len = ft_len_doublestr(strs) + 2;
	if (!(ret = (char **)ft_calloc(sizeof(char *), len--)))
		return (0);
	ret[--len] = ft_strdup(item);
	while (len--)
		if (!(ret[len] = ft_strdup(strs[len])))
			return (0);
	*strs_ref = ret;
	ft_free_doublestr(&strs);
	return (ret);
}
