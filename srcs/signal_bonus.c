/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:56:09 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/13 18:41:02 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void		signal_handler_builtin(int signo)
{	
	default_term_mode();
	ft_putchar_fd('\n', 1);
	if (signo == SIGINT)
	{
		display_prompt();
		set_res(1);
	}
	// else if (signo == SIGQUIT)
	// 	ft_putstr_fd("\b\b  \b\b", 1);
}

static void		signal_handler_exec(int signo)
{
	default_term_mode();
	ft_putchar_fd('\n', 1);
	if (signo == SIGINT)
	{
		set_res(130);
		signal(SIGINT, signal_handler_builtin);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		set_res(131);
		signal(SIGQUIT, signal_handler_builtin);
	}
}

void			set_exec_signal(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
	return ;
}

void			set_builtin_signal()
{
	signal(SIGINT, (void *)signal_handler_builtin);
	signal(SIGQUIT, (void *)signal_handler_builtin);
	return ;
}
