/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:36:45 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/08 01:57:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_strs(int size, char **strs, int sort)
{
	int		i;
	t_list	*lst;

	lst = 0;
	i = 0;
	if (sort == 1)
	{
		while (i < size)
			ft_lstadd_back(&lst, ft_lstnew(strs[i++]));
	}
	if (sort == 2)
	{
		while (i < size)
			ft_lstadd_front(&lst, ft_lstnew(strs[i++]));
	}
	return (lst);
}
