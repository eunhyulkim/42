/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:03:11 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 21:53:43 by iwoo             ###   ########.fr       */
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
	close_fd_and_pipes();
	ft_free(line);
	ft_putendl_fd("exit", 1);
	ft_free_doublestr(g_env);
	exit(status);
}

void			cmd_exit(t_command *command)
{
	close_fd_and_pipes();
	ft_putendl_fd("exit", 1);
	g_res = 0;
	if (command->arg_list)
	{
		if (!ft_isnumber(command->arg_list[0]))
			error_builtin("exit", command->arg_list[0], NUMERIC_REQUIRED);	
		else if (ft_len_doublestr(command->arg_list) > 1)
			return (error_builtin("exit", "\b\b  \b\b", TOO_MANY_ARG));
		else
			set_res(ft_atoi(command->arg_list[0]));
	}
	exit(g_res);
	return ;
}
