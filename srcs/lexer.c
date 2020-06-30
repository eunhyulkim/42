/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 23:09:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/30 13:13:02 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define    PIPE        'P' // !P-O-*, !P-SO-*, !P-*-X
# define    OR          'O'
# define    AND         'A'
# define    SEMI        'Y'
# define    DSEMI       'Z'
# define    GREATER     'G'
# define    DGREATER    'H'
# define    LESS        'L'
# define    DLESS       'M'
# define    SPACE       'S'
# define    EMPER       'E'
# define    NUMBER      'N'
# define    STRING      'C'
# define    ENTER       'F'

static char	type(char **tokens, int idx)
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

static int  check_order(char **tokens, int midx, char *format, char opt)
{
    int     i;
    int     len;

    i = 0;
    len = ft_len_doublestr(tokens);
    format = (opt == 'L') ? ft_strreverse(format) : format;
    while (format[i])
    {
        if (opt == 'L' && (midx - i - 1) < 0 && ft_free(format))
            return ((format[i] == 'X') ? TRUE : FALSE);
        if (opt == 'R' && (midx + i + 1) >= len)
            return ((format[i] == 'X') ? TRUE : FALSE);
        if (opt == 'L' && format[i] != type(tokens, midx - i - 1))
            if (!ft_isset(format[i], "W*") && ft_free(format))
                return (FALSE);
        if (opt == 'R' && format[i] != type(tokens, midx + i + 1))
            if (!ft_isset(format[i], "W*"))
                return (FALSE);
        i++;
    }
    if (opt == 'L')
        free(format);
    return (TRUE);
}

static int  token_in(char **tokens, int idx, char mid_type, char *format)
{
    int     i;
    char    **formats;
    char    **parts;

    i = -1;
    formats = ft_split(format, ',');
    while (formats[++i])
    {
        if (*(ft_strchr(formats[i], '-') + 1) != mid_type)
            continue;
        parts = ft_split(formats[i], '-');
        if (check_order(tokens, idx, parts[0], 'L'))
            if (check_order(tokens, idx, parts[2], 'R'))
                if (ft_free_doublestr(parts))
                    return (TRUE);
        ft_free_doublestr(parts);
    }
    ft_free_doublestr(formats);
    return (0);
}

static int	is_valid_token(char **tokens, int idx, char type)
{
    if (type == DSEMI)
        return (FALSE);
    if (token_in(tokens, idx, type, \
    "X-P-*,XS-P-*,*-P-X,*-P-SX,*-P-F,*-P-SF,\
    O-P-*,\
    OS-P-*,*-P-X"))
        return (FALSE);
    return (TRUE);
}

int     lexer(char **tokens)
{
	int			idx;
	char		mid_type;

	idx = 0;
	while (tokens[idx])
	{
		mid_type = type(tokens, idx);
        write(1, "[", 1);
        write(1, &mid_type, 1);
        write(1, "]", 1);
		if (!is_valid_token(tokens, idx, mid_type))
        {
            write(1, "\nsyntax error near unexpected token `", 37);
            write(1, tokens[idx], ft_strlen(tokens[idx]));
            write(1, "\n", 1);
			return (FALSE);
        }
        idx++;
	}
    printf("\n");
	return (TRUE);
}
