#ifndef PARSER_H
# define PARSER_H

# include	"minishell.h"
# include	"lexer.h"

# define	STDIN				0
# define	STDOUT				1
# define	X_BACK_GREAT		"*-G,*-H"

# define	BACK_REDIR			"*-G,*-SG,*-H,*-SH,*-L,*-SL,*-M,*-SM"
# define	FRONT_EMP_REDIR		"EG-*,EH-*,EL-*,EM-*"


typedef bool	has_cmd;
typedef bool	has_redirect;

typedef struct 	s_parser
{
	int			command;
	int			fd;
}				t_parser;

t_table		*get_last_table(t_table *table);
t_job		*get_last_job(t_table *table);
t_redir		*get_last_redir(t_table *table);
void		set_redir_file(char **tokens, t_lexer *lexer, \
			t_table *table);
void		set_command_cmd(char **tokens, t_lexer *lexer, \
			t_parser *parser, t_table *table);
void		set_command_arg(char **tokens, t_lexer *lexer, \
			t_table *table);

#endif
