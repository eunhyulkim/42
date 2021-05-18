/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:14:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/28 11:13:04 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_in(char *item, char *list)
{
	int		opened;
	int		ans;

	opened = 0;
	ans = 0;
	if (!item || !(*item) || !list || *list++ != '[')
		return (0);
	while (*list)
	{
		if (!opened && *list == '\'')
			opened = 1;
		else if (*list == '\'')
			opened = 0;
		else if (opened && *item == *list)
			if (!ans && !ft_strncmp(list, item, ft_strlen(item)))
				if (*(list + ft_strlen(item)) == '\'')
					ans = 1;
		list++;
	}
	if (opened || *(--list) != ']')
		return (0);
	return (ans);
}
