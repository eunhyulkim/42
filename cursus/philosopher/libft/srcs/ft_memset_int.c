/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 21:26:16 by eunhkim           #+#    #+#             */
/*   Updated: 2020/04/07 21:50:10 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memset_int_two(int *n1, int *n2, int v)
{
	*n1 = v;
	*n2 = v;
}

void	ft_memset_int_three(int *n1, int *n2, int *n3, int v)
{
	*n1 = v;
	*n2 = v;
	*n3 = v;
}

void	ft_memset_int_four(int *n1, int *n2, int *n3, int *n4)
{
	*n1 = 0;
	*n2 = 0;
	*n3 = 0;
	*n4 = 0;
}
