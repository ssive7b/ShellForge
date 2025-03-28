/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:12:15 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/25 14:14:48 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static size_t	number_words(char const *s, char c);
static char		*check_alloc(char **res, const char *bg, size_t len, size_t j);
static size_t	get_word_len(const char *s, char c);

char	**ft_split(char const *s, char c)
{
	char		**str_split;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str_split = (char **)malloc(sizeof(char *) * (number_words(s, c) + 1));
	if (!str_split)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!check_alloc(str_split, &s[i], get_word_len(&s[i], c), j++))
				return (NULL);
			i += get_word_len(&s[i], c);
		}
		else
			i++;
	}
	str_split[j] = NULL;
	return (str_split);
}

static size_t	number_words(char const *s, char c)
{
	size_t	i;
	int		new_word;

	i = 0;
	new_word = 1;
	while (*s)
	{
		if (*s != c)
		{
			if (new_word)
			{
				new_word = 0;
				i++;
			}
		}
		else
			new_word = 1;
		s++;
	}
	return (i);
}

static char	*check_alloc(char **res, const char *bg, size_t len, size_t j)
{
	res[j] = ft_substr(bg, 0, len);
	if (!res[j])
	{
		while (j > 0)
			free(res[--j]);
		free(res);
		return (NULL);
	}
	return (res[j]);
}

static size_t	get_word_len(const char *s, char c)
{
	char	*next_char;

	next_char = ft_strchr(s, c);
	if (next_char)
		return (next_char - s);
	return (ft_strlen(s));
}
/*
#include <stdio.h>
int	main(void)
{
	char		c = '^';
	char const	*s = "^^^1^^2a,^^^^3^^^^--h^^^^";
	size_t		num_words = number_words(s, c);
	char		**res = ft_split(s, c);
	size_t		i = 0;

	printf("number_words: %lu\n", number_words(s, c));
	while (num_words--)
	{
		printf("'%s'\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}
*/