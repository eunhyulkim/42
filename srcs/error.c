#include "minishell.h"

void	print_error(char *error_token, char *msg, int res)
{
	ft_putstr_fd(SHELL, 2);
	if (msg == LEXER_MSG)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(error_token, 2);
		ft_putendl_fd("\'", 2);
	}
	else if (msg == REDIR_AMB_MSG || msg == REDIR_FDERR_MSG
	|| msg == PERMISSION_MSG)
	{
		ft_putstr_fd(error_token, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
	g_res = res;
}
