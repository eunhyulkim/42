#include "minishell.h"
#include "execute.h"

int		cmd_exit(t_command *command)
{
	// close_all_opened_fd();
	(void)command;
	ft_putendl_fd("exit", 1);
	g_res = 0;
	return (0);
}
