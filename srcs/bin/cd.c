#include "minishell.h"
#include "execute.h"

void	cmd_cd(t_command *command)
{
	char	*current_pwd;
	char	*home_path;
	int		argc;

	argc = ft_len_doublestr(command->arg_list);
	if (argc > 1)
	{
		ft_putstr_fd("mongshell $: cd: too many arguments\n", 2);
	}
	else if (argc == 0)
	{
		home_path = get_env("HOME");
		if (chdir(home_path) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	printf("cmd_cd start\n");
	printf("%s\n", command->cmd);
	printf("%s\n", command->arg_list[0]);

	current_pwd = getcwd(NULL, PWD_BUFFER_SIZE);
	if (chdir(command->arg_list[0]) == -1)
	{
		ft_putstr_fd("Failed to change directory\n", 2);
		exit(-1);
	}
	free(current_pwd);
}
