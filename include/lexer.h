#ifndef LEXER_H
# define LEXER_H

/*
** for lexer.c
*/
# define    DSEMI       'Z'
# define    PIPE        'P' // !P-O-*, !P-SO-*, !P-*-X
# define    EMPER       'E'
# define    OR          'O'
# define    AND         'A'
# define    SEMI        'Y'
# define    GREATER     'G'
# define    DGREATER    'H'
# define    LESS        'L'
# define    DLESS       'M'
# define    SPACE       'S'
# define    NUMBER      'N'
# define    STRING      'C'
# define    ENTER       'F'

# define	FRONT_REDIR		"G-*,SG-*,H-*,SH-*,L-*,SL-*,M-*,SM-*"
# define 	NO_BACK_ARG		"*-X,*-SX,*-F,*-SF"
# define	FRONT_ALNUM		"N-*,C-*,SN-*,SC-*"

typedef struct	s_lexer
{
	int			len;
	int			idx;
	char		type;
	char		**seqs;
	char		**seq;
	char		**format;
	int			i;
	int			j;
	int			res;
}				t_lexer;

char	type(char **tokens, int idx);
int  	check_seq(char **tokens, t_lexer *lex);
int  	token_in(char **tokens, t_lexer *lex, char *format);

#endif
