/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:56:09 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/10 11:56:32 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		signal_handler_builtin(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putstr_fd("\n", 1);
		display_prompt();
		g_res = 1;
	}
	else if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

static void		signal_handler_exec(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_res = 130;
		signal(SIGINT, signal_handler_builtin);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_res = 131;
		signal(SIGQUIT, signal_handler_builtin);
	}
}

void			set_exec_signal(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	return ;
}

void			set_builtin_signal(void)
{
	signal(SIGINT, (void *)signal_handler_builtin);
	signal(SIGQUIT, (void *)signal_handler_builtin);
	return ;
}
