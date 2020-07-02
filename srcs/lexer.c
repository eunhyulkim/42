/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/02 14:20:32 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

char	type(char **tokens, int idx)
{
	if (!ft_strcmp(tokens[idx], "|"))
		return (PIPE);
    if (!ft_strcmp(tokens[idx], "||"))
        return (OR);
    if (!ft_strcmp(tokens[idx], "&"))
        return (EMPER);
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
    return (!ft_strcmp(tokens[idx], "\n") ? ENTER : STRING);
}

int     check_seq(char **tokens, t_lexer *lex)
{
	int		i;
	int		j;
	char	c;

    i = -1;
    while (++i < 2)
    {
		j = -1;
		while (lex->format[i][++j])
		{
			c = lex->format[i][j];
			if (lex->res == TRUE || lex->res == FALSE)
				break ;
			if ((i == 0 && (lex->idx - j - 1) < 0) \
			|| (i == 1 && (lex->idx + j + 1) >= lex->len))
				lex->res = (c == 'X') ? TRUE : FALSE;
			else if ((i == 0 && c != type(tokens, lex->idx - j - 1)) \
			|| (i == 1 && c != type(tokens, lex->idx + j + 1)))
				lex->res = (!ft_isset(c, "W*")) ? FALSE : -1;
		}
		if (lex->res == FALSE)
			break ;
    }
	ft_free_doublestr(lex->format);
    return (lex->res != FALSE);
}

int     token_in(char **tokens, t_lexer *lex, char *format)
{
    lex->i = -1;
    lex->seqs = ft_split(format, ',');
    lex->j = 0;
	while (lex->seqs[lex->j])
	{
		lex->format = ft_split(lex->seqs[lex->j], '-');
		lex->res = -1;
		if (check_seq(tokens, lex))
			return (ft_free_doublestr(lex->seqs));
		lex->j++;
	}
	ft_free_doublestr(lex->seqs);
    return (0);
}

static int	is_valid_token(char **tokens, t_lexer *lex)
{
    if (lex->type == DSEMI || lex->type == EMPER)
        return (FALSE);
	if (lex->type == STRING && !ft_isright_quote(tokens[lex->idx]))
		return (FALSE);
	if (ft_isset(lex->type, "GHLMF"))
		return (!token_in(tokens, lex, FRONT_REDIR));
	if (ft_isset(lex->type, "NCS"))
		return (TRUE);
    if (token_in(tokens, lex, NO_BACK_ARG))
	    return (FALSE);
    if (!token_in(tokens, lex, FRONT_ALNUM))
	    return (FALSE);
	return (TRUE);
}

int     lexer(char **tokens)
{
	t_lexer		*lex;

	if (!tokens || !(lex = ft_calloc(sizeof(t_lexer), 1)))
		return (0);
	lex->len = ft_len_doublestr(tokens);
	while (tokens[lex->idx])
	{
		lex->type = type(tokens, lex->idx);
        if (DEBUG_MODE)
        {
            write(1, "[", 1);
            write(1, &lex->type, 1);
            write(1, "]", 1);
        }
		if (!is_valid_token(tokens, lex))
        {
			write(1, "\nmongshell: syntax error near unexpected token `", 48);
                write(1, tokens[lex->idx], ft_strlen(tokens[lex->idx]));
                write(1, "\n", 1);
            free(lex);
			return (FALSE);
        }
        lex->idx++;
	}
    write(1, "\n", 1);
	free(lex);
	return (TRUE);
}
