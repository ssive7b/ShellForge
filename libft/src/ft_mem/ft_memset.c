/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:39:22 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/20 16:10:08 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}
/*
int	main(void)
{
	int	n = 3;
	int	arr[] = {1, 2, 3, 4, 5};

	ft_memset(arr, '1', n * sizeof(arr[0]));
	for (int i = 0; i < sizeof(arr)/ sizeof(arr[0]); i++)
		printf("%d ", arr[i]);
	printf("%ld\n", sizeof(arr[4]));
	return (0);
}
*/
