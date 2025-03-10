/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:49:36 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/24 23:50:20 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*begin;
	char const	*end;
	char		*trimmed_str;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	begin = s1;
	while (*begin && is_set(*begin, set))
		begin++;
	end = s1 + ft_strlen(s1) - 1;
	while (end > begin && is_set(*end, set))
		end--;
	len = end - begin + 1;
	trimmed_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, begin, len + 1);
	return (trimmed_str);
}

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
/*
int	main()
{
	char 	*str1 = "lorem ipsum sim et";
	char 	*str2 = "tel";

	printf("concat_str:'%s'\n",ft_strtrim(str1, str2));
	return (0);
}
*/