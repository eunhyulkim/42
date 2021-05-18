/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_doublestr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:13:49 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:13:49 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap(char **strs, int i, int j)
{
	char	*temp;

	temp = strs[i];
	strs[i] = strs[j];
	strs[j] = temp;
}

static int		partition(char **strs, int left, int right)
{
	char	*pivot;
	int		low;
	int		high;

	pivot = strs[left];
	low = left + 1;
	high = right;
	while (low <= high)
	{
		while (low <= right && ft_strcmp(pivot, strs[low]) >= 0)
			low++;
		while (high >= (left + 1) && ft_strcmp(pivot, strs[high]) <= 0)
			high--;
		if (low <= high)
			swap(strs, low, high);
	}
	swap(strs, left, high);
	return (high);
}

void			ft_sort_doublestr(char **strs, int left, int right)
{
	int	pivot;

	if (left > right)
		return ;
	pivot = partition(strs, left, right);
	ft_sort_doublestr(strs, left, pivot - 1);
	ft_sort_doublestr(strs, pivot + 1, right);
}
