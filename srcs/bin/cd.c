#include "minishell.h"

static void	set_pwd_and_g_res(char *path)
{
	set_env("PWD", path);
	g_res = 0;
	return ;
}

void		cmd_cd(t_command *command)
{
	char	*home_path;
	int		argc;

	argc = ft_len_doublestr(command->arg_list);
	if (argc == 0)
	{
		home_path = get_env("HOME");
		if (chdir(home_path) == -1)
			return (error_cmd("cd", ""));
		return (set_pwd_and_g_res(home_path));
	}
	if (chdir(command->arg_list[0]) == -1)
		return (error_cmd("cd", command->arg_list[0]));
	return (set_pwd_and_g_res(command->arg_list[0]));
}
