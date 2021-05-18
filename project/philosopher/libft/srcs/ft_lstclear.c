/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:28:56 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:13:04 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*item;
	t_list	*remove;

	if (!lst || !del)
		return ;
	item = *lst;
	while (item)
	{
		del(item->content);
		remove = item;
		item = item->next;
		free(remove);
	}
	*lst = NULL;
}
