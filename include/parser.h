#ifndef PARSER_H
# define PARSER_H

# include	"minishell.h"
# include	"lexer.h"

# define	X_BACK_GREAT		"*-G,*-H"

# define	BACK_REDIR			"*-G,*-SG,*-H,*-SH,*-L,*-SL,*-M,*-SM"
# define	FRONT_EMP_REDIR		"EG-*,EH-*,EL-*,EM-*"


typedef bool	has_cmd;
typedef bool	has_redirect;

typedef struct 	s_parser
{
	int			command;
}				t_parser;

#endif PARSER_H
