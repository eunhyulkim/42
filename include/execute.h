#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

# define TRUE	 	1
# define FALSE	 	0

# define OPENED		1
# define UNOPENED	0

# define N_OPTION	-2

typedef int		bool;

/*
** execute functions
*/

int		execute_redirection(t_table *table);
int		execute_command_list(t_table *table);

/*
**	in commands directory
*/

void	cmd_echo(t_command *cmd_list);	

# endif
