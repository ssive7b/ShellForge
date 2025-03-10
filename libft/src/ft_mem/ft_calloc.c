/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:09:29 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/23 21:09:49 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)(-1) / size)
		return (NULL);
	total_size = nmemb * size;
	buffer = (char *)malloc(total_size);
	if (!buffer)
		return (NULL);
	buffer = (char *)ft_memset(buffer, 0, total_size);
	return ((void *)buffer);
}
