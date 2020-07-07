#include "minishell.h"
#include "execute.h"

void	cmd_execve(t_command *command)
{
	struct stat	f_stat;

	if (check_bins(command))
		bin_execve(command);
	if (lstat(command->cmd, &f_stat) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(command->cmd, 1);
		ft_putendl_fd(": command not found", 1);
		g_res = 127;
		return ;
	}
	return ;
}
