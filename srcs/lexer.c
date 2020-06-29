/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/28 13:42:16 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define    PIPE        1
# define    OR          2
# define    AND         3
# define    SEMI        4
# define    DSEMI       5
# define    GREATER     6    
# define    DGREATER    7    
# define    LESS        8    
# define    DLESS       9    
# define    SPACE       10    
# define    NUMBER      11    
# define    STRING      12


// # define    COMMAND					4;
// # define    ARGUMENT				5;
// # define    PIPE					10;
// # define    REDIRECT				6;
// # define    FILENAME				7;
// # define    COMMAND_PARSE_MASK		5;
// # define    REDIRECT_PARSE_MASK		7;

/*
** command [arguments] | cmd [arguments] | ... | redirects filename
*/

/*
** ERROR_CASE(has_cmd, has_redirect)
** PIPE		5	0
** ARGUMENT	10	0
** COMMAND	4	1
** REDIRECT	6		1
** FILENAME	7		0
*/

static int	check_type(char **tokens, int idx)
{
	if (!ft_strcmp(tokens[idx], "|"))
		return (PIPE);
    if (!ft_strcmp(tokens[idx], "||"))
        return (OR);
    if (!ft_strcmp(tokens[idx], "&&"))
        return (AND);
    if (!ft_strcmp(tokens[idx], ";"))
        return (SEMI);
    if (!ft_strcmp(tokens[idx], ";;"))
        return (DSEMI);
    if (!ft_strcmp(tokens[idx], ">"))
        return (GREATER);
    if (!ft_strcmp(tokens[idx], ">>"))
        return (DGREATER);
    if (!ft_strcmp(tokens[idx], "<"))
        return (LESS);
    if (!ft_strcmp(tokens[idx], "<<"))
        return (DLESS);
    if (ft_isformat(tokens[idx], " +"))
        return (SPACE);
    if (ft_isformat(tokens[idx], "d+"))
        return (NUMBER);
    return (STRING);
}

static int	is_valid_token(char **tokens, int idx, int type)
{
    int     prev;
    int     pprev;

    prev = (idx) ? check_type(tokens[idx - 1]) : 0;
    pprev = (idx - 1) ? check_type(tokens[idx - 2]) : 0;
    if (type == DSEMI)
        return (FALSE);
    if (type == PIPE && prev == SEMI || (prev == SPACE && pprev == SEMI)
    return (TRUE);

	// err = FALSE;
	// if (type == COMMAND && table->has_cmd == TRUE)
	// 	err = TRUE;
	// else if ((type == PIPE || type == ARGUMENT) && table->has_cmd == FALSE)
	// 	err = TRUE;
	// else if (type == REDIRECT && table->has_redirect == TRUE)
	// 	err = TRUE;
	// else if (type == FILENAME && table->has_redirect == FALSE)
	// 	err = TRUE;
	// write(1, "syntax error near unexp")
	// return (err) ? TRUE : FALSE;
}

int     lexer(char **tokens)
{
	int			idx;
	int			type;

	idx = 0;
	while (tokens[idx])
	{
		type = check_type(tokens, idx);
        printf("[%d]", type);
		if (is_valid_token(tokens, idx, type))
        {
            write(1, "syntax error near unexpected token `", 36);
            write(1, tokens[idx], ft_strlen(tokens[idx]));
            write(1, "\'\n", 2);
			return (FALSE);
        }
        idx++;
	}
    printf("\n");
	return (TRUE);
}