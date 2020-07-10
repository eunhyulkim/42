/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwoo <iwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 21:34:02 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/10 21:34:23 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd_and_res(char *path)
{
	set_env("PWD", path);
	set_res(0);
	return ;
}

void		cmd_cd(t_command *command)
{
	char	*home_path;
	int		argc;

	argc = ft_len_doublestr(command->arg_list);
	if (argc == 0)
	{
		home_path = get_env("HOME");
		if (chdir(home_path) == -1)
			return (error_builtin("cd", "", ""));
		return (set_pwd_and_res(home_path));
	}
	if (chdir(command->arg_list[0]) == -1)
		return (error_builtin("cd", command->arg_list[0], ""));
	return (set_pwd_and_res(command->arg_list[0]));
}
