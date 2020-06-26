/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_doublestr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 21:45:20 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 21:56:21 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_doublestr(char **strs, char *item)
{
	char	**ret;
	int		len;

	len = ft_len_doublestr(strs);
	if (!(ret = (char **)ft_calloc(sizeof(char *), len + 2)))
		return (0);
	ret[--len] = ft_strdup(item);
	while (len--)
		if (!(ret[len] = ft_strdup(strs[len])))
			return (0);
	return (ret);
}
