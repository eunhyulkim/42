#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

# define DEBUG_ALL		0
# define DEBUG_LEXER	0
# define DEBUG_PARSER	0
# define DEBUG_TABLE	0
# define DEBUG_CONVERT	0

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

typedef struct 			s_redir
{
	char				*sign;
	int					fd;
	char				*arg;
	struct s_redir		*next;
}						t_redir;

typedef struct 			s_command
{
	char				*cmd;
	char				**arg_list;
}						t_command;

typedef struct			s_job
{
	struct s_command	command;
	struct s_redir		*redir_list;
	int					fd[2];
	struct s_job		*next;
}						t_job;

typedef struct  		s_table
{
	struct s_job		*job_list;
	int					sep_type; // &&, ||, ; 중 어느 sep로 나누어진 table인지 저장
	struct s_table		*next;
}						t_table;

char					**g_env;
int						g_res;

/*
** display functions
*/
void			clear_terminal(void);
int				print_ascii_art(void);
void			display_logo(void);
void			display_prompt(void);

/*
** tokenizer function
*/
char			**tokenizer(char *line);

/*
** lexer function
*/
int				lexer(char **tokens);

/*
** parser functions
*/
t_table			*parser(char **tokens);

/*
** converter
*/
void			converter(t_table *table);

/*
** bin/env functions
*/
void			init_env(char **env);
char			*get_env(char *key);
int				set_env(char *key, char *val);

/*
** free functions
*/
void			free_table(t_table *table);

/*
** debug functions
*/

void			print_table(t_table *table);

# endif
