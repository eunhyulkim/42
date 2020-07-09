#include "minishell.h"
#include "execute.h"

void	print_echo_args(char **arg_list, int option)
{
	int i;
	int	is_first_argu;

	if (!arg_list)
		return ;
	is_first_argu = TRUE;
	i = -1;
	while (arg_list[++i])
	{
		if (is_first_argu == FALSE) ft_putstr_fd(" ", 1);
		ft_putstr_fd(arg_list[i], 1);
		is_first_argu = FALSE;
	}
	g_res = 0;
	if (option == N_OPTION)
		return ;
	ft_putstr_fd("\n", 1);
}

void	cmd_echo(t_command *cmd)
{
	int		argu_era;
	char	**start_argu;
	int		option;

	argu_era = ft_len_doublestr(cmd->arg_list);
	start_argu = cmd->arg_list;
	option = FALSE;
	if (argu_era == 0)
	{
		ft_putstr_fd("\n", 1);
		g_res = 0;
		return ;
	}
	if (!ft_strcmp(cmd->arg_list[0], "-n"))
	{
		if (argu_era == 1)
			return ;
		option = N_OPTION;
		start_argu++;
	}
	print_echo_args(start_argu, option);
}
