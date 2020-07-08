#include "minishell.h"

//TODO: make core dump when get SIGQUIT
void	signal_handler_of_child(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_res = 130;
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_res = 131;
	}
	exit(-1);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
		g_res = 1;
	}
	else if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}
