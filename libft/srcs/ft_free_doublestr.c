/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_doublestr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:06:55 by iwoo              #+#    #+#             */
/*   Updated: 2020/06/26 19:24:58 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_doublestr(char **doublestr)
{
	int i;

	if (!doublestr)
		return ;
	i = -1;
	while (doublestr[++i])
		free(doublestr[i]);
	free(doublestr);
}
