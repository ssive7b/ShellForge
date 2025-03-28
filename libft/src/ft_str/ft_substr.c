/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:04:23 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/24 17:20:45 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_len;
	size_t	len_max_possible;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	len_max_possible = s_len - start;
	if (len < len_max_possible)
		len_max_possible = len;
	sub_s = (char *)malloc(sizeof(char) * (len_max_possible + 1));
	if (!sub_s)
		return (NULL);
	while ((i < len_max_possible) && (s[start + i] != '\0'))
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
/*
int	main()
{
	char 	*original = "lorem ipsum dolor sit amet";
	char 	*sub_str;

	sub_str = ft_substr(original, 50, 10);
	printf("sub_str:'%s'\n",sub_str);
	return (0);
}
*/