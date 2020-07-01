#ifndef PARSER_H
# define PARSER_H

# define	X_BACK_REDIR		"*-G,*-H,*-L,*-M"
# define	BACK_REDIR			"*-G,*-SG,*-H,*-SH,*-L,*-SL,*-M,*-SM"
# define	FRONT_EMP_REDIR		"EG-*,EH-*,EL-*,EM-*"


typedef bool	has_cmd;
typedef bool	has_redirect;

typedef struct 	s_parser
{
	int			cmd;
}				t_parser;

#endif PARSER_H
