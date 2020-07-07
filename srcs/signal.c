#include "minishell.h"

//TODO: make core dump when get SIGQUIT
//TODO: test with child process
void	signal_handler_of_child(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
		signal(SIGINT, (void *)signal_handler);
		exit(0);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 2);
		signal(SIGQUIT, (void *)signal_handler);
		exit(-1);
	}
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
		signal(SIGINT, (void *)signal_handler);
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		signal(SIGQUIT, (void *)signal_handler);
		return ;
	}
}
