/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 19:12:37 by iwoo              #+#    #+#             */ /*   Updated: 2020/07/05 22:47:17 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

void	cmd_pwd(t_command *command)
{
	char *path;

	if (command->arg_list)
	{
		ft_putstr_fd("pwd can't get any arguments\n", 2);
		g_res = 127;
		return ;
	}
	path = getcwd(NULL, PWD_BUFFER_SIZE);
	if (!path)
	{
		ft_putstr_fd("Failed to get path, please check 'PWD_BUFFER_SIZE'\n", 2);
		g_res = 127;
		free(path);
		return ;
	}
	set_env("PWD", path);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	return ;
}
