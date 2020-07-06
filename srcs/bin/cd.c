#include "minishell.h"
#include "execute.h"

void	cmd_cd(t_command *command)
{
	char	*error_msg;
	char	*home_path;
	int		argc;

	argc = ft_len_doublestr(command->arg_list);
	if (argc > 1)
	{
		ft_putstr_fd("mongshell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		g_res = 127;
		return ;
	}
	else if (argc == 0)
	{
		home_path = get_env("HOME");
		if (chdir(home_path) == -1)
		{
			ft_putstr_fd("mongshell: ", 2);
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			g_res = 127;
			return ;
		}
		g_res = 0;
		return ;
	}
	if (chdir(command->arg_list[0]) == -1)
	{
		ft_putstr_fd("mongshell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(command->arg_list[0], 2);
		ft_putstr_fd(": ", 2);
		error_msg = strerror(errno);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
		g_res = 127;
		return ;
	}
	g_res = 0;
}
