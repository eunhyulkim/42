/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 19:12:37 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/05 22:23:06 by iwoo             ###   ########.fr       */
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
		exit(-1);
	}
	path = get_env("PWD");
	if (!path)
	{
		ft_putstr_fd("Failed to get path\n", 2);
		exit(-1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
