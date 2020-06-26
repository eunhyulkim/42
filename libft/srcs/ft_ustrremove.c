/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:39:41 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/06 00:42:09 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uchar			*ft_ustrremove(t_uchar *dest, t_uchar *str)
{
	t_uchar		*result;

	if (!dest || !str)
		return (dest);
	*str = 0;
	result = ft_ustrdup(dest);
	free(dest);
	return (result);
}
