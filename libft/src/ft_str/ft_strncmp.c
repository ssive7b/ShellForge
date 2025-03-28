/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:07 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/22 16:31:36 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	while (*s1 == *s2 && --n && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/*
int main()
{
    const char   *s1= "t1st\200";
    const char   *s2= "test\0";
	size_t	n = -2;

    printf("ft_strncmp: '%d'\n", ft_strncmp(s1, s2, n));
    printf("strncmp: '%d'\n", strncmp(s1, s2, n));

    return (0);
}
*/