/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:50:48 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/24 22:51:01 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_concat;
	char	*temp;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str_concat = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_concat)
		return (NULL);
	temp = str_concat;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (str_concat);
}
/*
int	main()
{
	char 	*str1 = "lorem ipsum";
	char 	*str2 = "dolor sit amet";

	printf("concat_str:'%s'\n",ft_strjoin(str1, str2));
	return (0);
}
*/