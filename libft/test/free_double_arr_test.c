/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:54:40 by iwoo              #+#    #+#             */
/*   Updated: 2020/06/26 17:26:37 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int main(void)
{
	char **lines;

	char *line_1;
	char *line_2;
	char *line_3;

	line_1 = ft_strdup("123");
	line_2 = ft_strdup("abc");
	line_3 = ft_strdup("ABC");

	lines = (char **)malloc(sizeof(char *) * 4);
	lines[0] = line_1;
	lines[1] = line_2;
	lines[2] = line_3;
	lines[3] = NULL;
	
	int i = -1;
	while (lines[++i])
		printf("%s\n", lines[i]);

//	for (int i = 0; i < 4; i++)
//		free(lines[i]);
//	free(lines);

	free_double_arr(lines);
//	free(line_1);
//  free(line_2);
//	free(line_3);
	free(lines);

	return (0);
}
