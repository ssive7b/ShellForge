/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:58:17 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/20 17:34:53 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = n;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else if (s < d)
	{
		while (i--)
			d[i] = s[i];
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	void	*result;
	char	*dest = NULL;
	const char	*src = 0;
	result = memcpy(NULL, NULL, 0);
	result = memmove(NULL, NULL, 10);
	printf("memcpy: %p\n", dest);
	printf("memmove: %p\n", dest);
	return (0);
}
*/
