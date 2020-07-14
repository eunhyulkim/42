/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:27:37 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 17:00:52 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	ft_dlstadd(t_dlist **head, t_dlist *new)
{
	t_dlist	*ptr;

	ptr = NULL;
	if (!new || !head)
		return ;
	new->next = *head;
	if (*head)
	{
		ptr = (*head)->prev;
		(*head)->prev = new;
	}
	new->prev = ptr;
	if (ptr)
		ptr->next = new;
	*head = new;
}

t_dlist	*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*new_node;

	new_node = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_dlist));
	if (!content)
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	else
	{
		new_node->content = (void *)malloc(content_size);
		if (!new_node->content)
			return (NULL);
		ft_memcpy(new_node->content, content, content_size);
		new_node->content_size = content_size;
	}
	return (new_node);
}

size_t	ft_dlstsize(t_dlist *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_dlstremovenode(t_dlist **head)
{
	t_dlist	*ptr;

	if (*head)
	{
		if ((*head)->prev)
			(*head)->prev->next = (*head)->next;
		if ((*head)->next)
			(*head)->next->prev = (*head)->prev;
		ptr = *head;
		*head = (*head)->next ? (*head)->next : (*head)->prev;
		free(ptr->content);
		free(ptr);
	}
}

void	ft_dlstdelstr(t_dlist **lst)
{
	t_dlist *tmp;
	t_dlist *dlst;

	dlst = *lst;
	while (dlst)
	{
		if (dlst->prev)
			dlst = dlst->prev;
		else
			break ;
	}
	*lst = dlst;
	while (*lst)
	{
		tmp = *lst;
		free((*lst)->content);
		*lst = (*lst)->next;
		free(tmp);
	}
}
