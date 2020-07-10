/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:41:18 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 20:10:10 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_tokenizer(char *error_token, char *msg, int res)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(error_token, 2);
	ft_putendl_fd("\'", 2);
	set_res(res);
}

void	error_execute(char *error_token, char *msg, int res)
{
	ft_putstr_fd(SHELL, 2);
	if (error_token)
	{
		ft_putstr_fd(error_token, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	set_res(res);
}

void	error_builtin(char *cmd, char *arg)
{
	int error_num;

	error_num = errno;
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error_num), 2);
	set_res(1);
	return ;
}
