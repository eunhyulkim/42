/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:50:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/11 20:35:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_empty_line(char *line)
{
	int		i;

	if (!line)
		return (TRUE);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' && !line[i + 1])
	{
		ft_free(line);
		return (TRUE);
	}
	return (FALSE);
}

static int		process_line(char *line)
{
	char		**tokens;
	t_table		*table;
	t_table		*first_table;

	tokens = tokenizer(line);
	ft_free(line);
	if (!lexer(tokens) || !(table = parser(tokens)))
		return (TRUE);
	first_table = table;
	while (table)
	{
		expander(table);
		converter(table);
		execute_table(table);
		table = table->next;
	}
	ft_free_doublestr(tokens);
	free_tables(first_table);
	return (TRUE);
}

int				main(int ac, char *av[], char **env)
{
	char	*line;

	display_logo();
	init_env(ac, av, env);
	while (TRUE)
	{
		set_builtin_signal();
		display_prompt();
		line = 0;
		if (!(get_next_line(0, &line)))
			ft_exit(line, 0);
		else if (is_empty_line(line))
			continue;
		process_line(line);
	}
	return (0);
}
