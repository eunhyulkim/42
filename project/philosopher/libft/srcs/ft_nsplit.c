/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:32:30 by eunhkim           #+#    #+#             */
/*   Updated: 2020/06/26 11:27:33 by eunhkim          ###   ########.fr       */
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

static int	*calc_word_lens(const char *str, char sep, int size)
{
	int		i;
	int		j;
	int		*lens;

	if (!(lens = ft_calloc(sizeof(int), size)))
		return (0);
	i = 0;
	j = -1;
	while (str[i] != '\0')
	{
		if (is_word(str, i, sep) && size)
		{
			lens[++j] += 1;
			size--;
		}
		else if (str[i] != sep)
			lens[j] += 1;
		i++;
	}
	return (lens);
}

static int	split_process(char const *s, char **words, char sep, int *lens)
{
	int		si;
	int		wi;
	int		ci;

	si = -1;
	wi = -1;
	while (s[++si] != '\0')
	{
		if (is_word(s, si, sep))
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

static int	split_process(char const *s, char **words, char sep, int *lens)
{
	int		wi;
	int		ci;
	int		cnt;

	wi = 0;
	ci = 0;
	while (lens[wi] != 0)
	{
		if (!(words[wi] = (char *)ft_calloc(sizeof(char), (lens[wi] + 1))))
			return (0);

		wi++;
	}

}

char		**ft_nsplit(char const *s, char sep, int size)
{
	char	**words;
	int		*lens;

	if (!s)
		return (0);
	if (!(words = (char **)ft_calloc(sizeof(char *), (size + 1))))
		return (0);
	if (!(lens = calc_word_lens(s, sep, size)))
		return (0);
	if (!(split_process(s, words, sep, lens)))
		return (0);
	free(lens);
	return (words);
}
