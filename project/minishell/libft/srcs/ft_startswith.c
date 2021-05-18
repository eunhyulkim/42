/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:32:48 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 19:34:18 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_startswith(const char *str, const char *sub)
{
	int		i;

	i = 0;
	while (sub[i] != '\0' && str[i] == sub[i])
		i++;
	return (sub[i] == '\0');
}
