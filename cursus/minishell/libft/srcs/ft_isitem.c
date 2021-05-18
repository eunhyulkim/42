/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isitem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:14:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/28 11:27:21 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isitem(char *item, char **list)
{
	int		idx;

	if (!item || !(*item) || !list || !(*list))
		return (0);
	idx = 0;
	while (list[idx])
	{
		if (*item == *(list[idx]) && !ft_strcmp(list[idx], item))
			return (1);
		idx++;
	}
	return (0);
}
