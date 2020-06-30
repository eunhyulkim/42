#include "minishell.h"

void	print_echo_args(char **argu_list, int option)
{
	int i;
	int	is_first_argu;

	if (!argu_list)
		return ;
	is_first_argu = TRUE;
	i = -1;
	while (argu_list[++i])
	{
		if (is_first_argu == FALSE)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(argu_list[i], 1);
		is_first_argu = FALSE;
	}
	if (option == N_OPTION)
		exit(0);
	ft_putstr_fd("\n", 1);
	exit(0);
}

void	cmd_echo(t_command *cmd)
{
	int		argu_era;
	char	**start_argu;
	int		option;

	argu_era = ft_len_doublestr(cmd->argu_list);
	start_argu = cmd->argu_list;
	option = FALSE;
	if (argu_era == 0)
	{
		ft_putstr_fd("\n", 1);
		exit(0);
	}
	if (!ft_strcmp(cmd->argu_list[0], "-n"))
	{
		if (argu_era == 1)
			exit(0);
		option = N_OPTION;
		start_argu++;
	}
	print_echo_args(start_argu, option);
}
