/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:05:01 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/09 17:05:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char **ptr, char c)
{
	char	*ret;
	int		size;

	if (!ptr)
		return (0);
	size = ft_strlen(*ptr);
	if (!(ret = (char *)ft_calloc(sizeof(char), size + 2)))
		return (0);
	ft_memcpy(ret, *ptr, size);
	ret[size] = c;
	ft_free(*ptr);
	*ptr = ret;
	return (ret);
}
