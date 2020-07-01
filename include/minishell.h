#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define DEBUG_MODE		1
# define TRUE	 		1
# define FALSE	 		0

typedef int				bool;

typedef struct  		s_tokenizer
{
	int					idx;
	int					qidx;
	int					start;
	int					prev;
	char				quote;
}						t_tokenizer;

typedef struct 			s_command
{
	char				*cmd;
	char				**arg_list;
	struct s_command	*next;
}						t_command;

typedef struct 			s_redir
{
	char				*sign;
	char				*arg;
	struct s_redir		*next;
}						t_redir;

typedef struct  		s_table
{
	struct s_command	*cmd_list;
	struct s_redirect	*redir_list;
	int					input_fd;
	int					output_fd;
	struct s_table		*next;
	struct s_table		*before;
	int					res;
	int					sep_state;
}						t_table;

char					**g_env;

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
char	**tokenizer(char *line);

/*
** lexer function
*/
int		lexer(char **tokens);

/*
** bin/env functions
*/
void	init_env(char **env);
char	*get_env(char *key);
int		set_env(char *key, char *val);

# endif
