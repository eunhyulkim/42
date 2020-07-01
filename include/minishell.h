#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "execute.h"

# define DEBUG_MODE		1
# define TRUE	 		1
# define FALSE	 		0

typedef int		bool;
typedef struct  s_tokenizer
{
	int			idx;
	int			qidx;
	int			start;
	int			prev;
	char		quote;
}				t_tokenizer;

char			**g_env;

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
