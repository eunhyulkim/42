/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:39:41 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:39:42 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strremove(char *dest, char *str, int opt)
{
	char	*remove_spot;
	char	*result;

	if (!dest || !str)
		return (dest);
	remove_spot = (opt == 1) ? ft_strnstr(dest, str, ft_strlen(dest)) : str;
	if (!remove_spot)
		return (dest);
	*remove_spot = 0;
	result = ft_strdup(dest);
	free(dest);
	return (result);
}
