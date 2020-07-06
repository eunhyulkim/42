#include "minishell.h"
#include "execute.h"

int		cmd_exit(t_command *command)
{
	close_all_opened_fd();
	putstr_exit();
	return (0);
}
