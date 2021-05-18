/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:00:13 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/14 16:05:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_handle(int *opened, char c)
{
	int		ret;

	ret = 0;
	if (!(*opened) && ft_isset(c, "\'\""))
	{
		*opened = c;
		ret = 1;
	}
	else if (*opened && *opened == c)
	{
		*opened = 0;
		ret = 1;
	}
	return (ret);
}
