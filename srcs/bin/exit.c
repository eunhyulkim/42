#include "minishell.h"
#include "execute.h"

int		cmd_exit(t_command *command)
{
	close_fd_and_pipes();
	(void)command;
	ft_putendl_fd("exit", 1);
	if (command->arg_list)
		g_res = ft_atoi(command->arg_list[0]);
	exit(g_res);
	return (0);
}
