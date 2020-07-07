#include "minishell.h"

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
