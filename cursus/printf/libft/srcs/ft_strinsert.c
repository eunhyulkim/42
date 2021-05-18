/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:39:41 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:34:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *dest, char *str, char *src)
{
	char	c;
	char	*origin;
	char	*insert_spot;

	if (!dest || !str || !src)
		return (dest);
	origin = dest;
	insert_spot = ft_strnstr(dest, str, ft_strlen(dest));
	if (!insert_spot)
		return (dest);
	c = *insert_spot;
	*insert_spot = 0;
	dest = ft_strdup(dest);
	*insert_spot = c;
	insert_spot = ft_strdup(insert_spot);
	dest = ft_strmjoin(dest, ft_strdup(src));
	dest = ft_strmjoin(dest, insert_spot);
	free(origin);
	return (dest);
}
