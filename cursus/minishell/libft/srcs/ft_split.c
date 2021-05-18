/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:32:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/07/05 17:11:01 by iwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_word(const char *str, int i, char sep)
{
	if (i == 0 && str[i] != sep)
		return (1);
	if (i > 0 && str[i - 1] == sep && str[i] != sep)
		return (1);
	return (0);
}

static int	word_count(const char *str, char c)
{
	int		i;
	int		count;

	count = 0;
	if (str[0] && str[0] != c)
		count++;
	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i - 1] == c && str[i] != c)
			count++;
	}
	return (count);
}

static int	*calc_word_lens(const char *str, char sep)
{
	int		i;
	int		j;
	int		*lens;
	int		word_cnt;

	word_cnt = word_count(str, sep);
	if (!(lens = malloc(sizeof(int) * word_cnt)))
		return (0);
	ft_memset(lens, 0, sizeof(int) * word_cnt);
	i = 0;
	j = -1;
	while (str[i] != '\0')
	{
		if (is_word(str, i, sep))
			lens[++j] += 1;
		else if (str[i] != sep)
			lens[j] += 1;
		i++;
	}
	return (lens);
}

static int	split_process(char const *s, char **words, char c, int *lens)
{
	int		si;
	int		wi;
	int		ci;

	si = -1;
	wi = -1;
	while (s[++si] != '\0')
	{
		if (is_word(s, si, c))
		{
			wi++;
			ci = 0;
			if (!(words[wi] = (char *)malloc(sizeof(char) * (lens[wi] + 1))))
				return (0);
			words[wi][lens[wi]] = '\0';
			words[wi][ci] = s[si];
		}
		else if (s[si] != c)
			words[wi][++ci] = s[si];
	}
	words[++wi] = 0;
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**words;
	int		*lens;

	if (!s)
		return (0);
	if (!(words = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (0);
	if (!(lens = calc_word_lens(s, c)))
		return (0);
	if (!(split_process(s, words, c, lens)))
		return (0);
	free(lens);
	return (words);
}
