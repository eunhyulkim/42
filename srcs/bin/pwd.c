/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 20:42:06 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/10 21:34:52 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(void)
{
	char *path;

	path = getcwd(NULL, PWD_BUFFER_SIZE);
	if (!path)
		return (error_builtin("env", "", FAIL_TO_GET_PATH));
	ft_putendl_fd(path, 1);
	ft_free(path);
	return (set_res(0));
}
