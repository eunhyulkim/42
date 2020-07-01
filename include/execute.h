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

typedef struct		s_command
{
	char				*cmd;
	char				**argu_list;
	struct s_command	*next;
}					t_command;

typedef struct		s_redi
{
	char				*redi;
	char				*argu;
	struct	s_redi		*next;
}					t_redi;

typedef struct		s_table
{
	t_command		*cmd_list;
	t_redi			*redi_list;
	int				input_fd;
	int				output_fd;
	struct s_table	*next;
	struct s_table	*before;
	int				res;			// table 연산이 끝났는지,  끝났다면 결과가 True/False 여부 저장
	int				sep_state;		// &&, ||, ; 중 어느 sep로 나누어진 table인지 저장
}					t_table;

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
