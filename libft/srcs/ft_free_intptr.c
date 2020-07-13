/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_intptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:22:36 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 12:22:36 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_intptr(int **intptr)
{
	if (!intptr || !(*intptr))
		return (0);
	free(*intptr);
	*intptr = 0;
	return (1);
}
