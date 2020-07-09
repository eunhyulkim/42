#include "minishell.h"

void	signal_handler_in_run_exec(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_res = 130;
		signal(SIGINT, signal_handler);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_res = 131;
		signal(SIGQUIT, signal_handler);
	}
}

void	signal_handler(int signo)
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
