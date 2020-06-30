#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE	 	1
# define FALSE	 	0

# define OPENED		1
# define UNOPENED	0

typedef int		bool;
typedef struct  s_tokenizer
{
	int			idx;
	int			start;
	int			prev;
	char		quote;
}				t_tokenizer;

char			**g_env;

typedef struct		s_command
{
	char				*cmd;
	char				*argu;
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
** display functions
*/
void	clear_terminal(void);
int		print_ascii_art(void);
void	display_logo(void);
void	display_prompt(void);

/*
** tokenizer function
*/
char	**tokenzier(char *line);

/*
** bin/env functions
*/
void	init_env(char **env);
char	*get_env(char *key);
int		set_env(char *key, char *val);

/*
** execute functions
*/

int		execute_redirection(t_table *table);
int		execute_command(t_table *table);

# endif
