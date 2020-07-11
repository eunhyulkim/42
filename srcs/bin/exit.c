/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:03:11 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 22:41:29 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_res(int res)
{
	g_res = res;
	return ;
}

void			ft_exit(char *line, int status)
{
	close_fd_and_pipes();
	ft_free_str(&line);
	ft_putendl_fd("exit", 1);
	ft_free_doublestr(&g_env);
	exit(status);
}

void			cmd_exit(t_command *command)
{
	close_fd_and_pipes();
	ft_putendl_fd("exit", 1);
	set_res(0);
	if (command->arg_list)
	{
		if (!ft_isnumber(command->arg_list[0]))
		{
			error_builtin("exit", command->arg_list[0], NUMERIC_REQUIRED);
			set_res(255);
		}
		else if (ft_len_doublestr(command->arg_list) > 1)
			return (error_builtin("exit", "\b\b  \b\b", TOO_MANY_ARG));
		else
			set_res(ft_atoi(command->arg_list[0]));
	}
	exit(g_res);
	return ;
}
