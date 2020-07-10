/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_doublestr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:06:55 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/09 21:55:01 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_doublestr(char **doublestr)
{
	int i;

	if (!doublestr)
		return (0);
	i = -1;
	while (doublestr[++i])
		free(doublestr[i]);
	free(doublestr);
	return (1);
}
