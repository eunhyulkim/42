/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:52:31 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:08:47 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	has_wild(char *str)
{
	if (!ft_strchr(str, '*'))
		return (0);
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (0);
	return (1);
}

char			**get_entries(char *mask)
{
	char			**entries;
	struct dirent	*item;
	DIR				*dp;

	if (!has_wild(mask))
		return (0);
	if (!(dp = opendir(get_env("PWD"))))
		return (0);
	item = readdir(dp);
	entries = 0;
	while (TRUE)
	{
		if (!(item = readdir(dp)))
			break ;
		if (*item->d_name != '.' && ft_isformat2(item->d_name, mask))
			ft_realloc_doublestr(&entries, item->d_name);
	}
	closedir(dp);
	return (entries);
}
