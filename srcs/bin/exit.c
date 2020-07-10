/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:03:11 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 20:48:00 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_isnumber(char *str)
{
	if (!str || !(*str))
		return (FALSE);
	while (*str && *str >= 48 && *str <= 57)
		str++;
	return (*str == '\0');
}

void			set_res(int res)
{
	g_res = res;
	return ;
}

void			ft_exit(char *line, int status)
{
	ft_free(line);
	ft_putstr_fd("exit\n", 1);
	ft_free_doublestr(g_env);
	exit(status);
	return ;
}

void			cmd_exit(t_command *command)
{
	close_fd_and_pipes();
	(void)command;
	ft_putendl_fd("exit", 1);
	g_res = 0;
	if (command->arg_list)
	{
		if (ft_len_doublestr(command->arg_list) > 1)
		{
			g_res = 1;
			ft_putstr_fd("mongshell: ", 1);
			ft_putstr_fd("exit: ", 1);
			ft_putendl_fd("too many arguments", 1);
		}
		else if (!ft_isnumber(command->arg_list[0]))
		{
			error_builtin("exit", command->arg_list[0], NUMERIC_ARG_REQUIRED);	
//			g_res = 1;
//			ft_putstr_fd("mongshell: ", 2);
//			ft_putstr_fd("exit: ", 2);
//			ft_putendl_fd("numeric argument required", 2);
		}
		else
			g_res = ft_atoi(command->arg_list[0]);
	}
	exit(g_res);
	return ;
}
