/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 21:34:30 by iwoo              #+#    #+#             */
/*   Updated: 2020/07/11 21:48:28 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_args(char **arg_list, int n_option)
{
	int i;
	int	is_first_arg;

	if (!arg_list)
		return ;
	is_first_arg = TRUE;
	i = -1;
	while (arg_list[++i])
	{
		if (is_first_arg == FALSE)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(arg_list[i], 1);
		is_first_arg = FALSE;
	}
	set_res(0);
	if (n_option)
		return ;
	ft_putstr_fd("\n", 1);
}

void	cmd_echo(t_command *cmd)
{
	int		len;
	char	**start_arg;
	int		n_option;

	len = ft_len_doublestr(cmd->arg_list);
	start_arg = cmd->arg_list;
	n_option = FALSE;
	if (len == 0)
	{
		ft_putstr_fd("\n", 1);
		return (set_res(0));
	}
	if (!ft_strcmp(cmd->arg_list[0], "-n"))
	{
		if (len == 1)
			return ;
		n_option = TRUE;
		start_arg++;
	}
	print_echo_args(start_arg, n_option);
}
