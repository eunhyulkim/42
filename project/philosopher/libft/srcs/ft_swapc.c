/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:09:10 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/05 23:14:25 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_swapc(char *s1, char *s2)
{
	char temp;

	if (!s1 || !s2)
		return (0);
	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
	return (1);
}
