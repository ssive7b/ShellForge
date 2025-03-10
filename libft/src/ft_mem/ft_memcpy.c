/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:47:13 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/20 16:22:33 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest[100];
	memset(dest, 'A', 100);
	char *rtn = (char *)ft_memcpy(dest, NULL, 0);
	printf("dest: \t'%s'\n", dest);
	printf("rtn: \t'%s'\n", rtn);
	printf("dest[0]: \t%c\n", dest[0]);
	printf("rtn==dest: \t%d\n", rtn==dest);
	printf("dest[0]='A': \t%d\n", dest[0]=='A');

	return (0);
}
*/
