/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:06:55 by iwoo              #+#    #+#             */
/*   Updated: 2020/06/26 17:07:38 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_arr(char **double_arr)
{
	int i;

	i = -1;
	while (double_arr[++i])
		free(double_arr[i]);
	free(double_arr);
}
