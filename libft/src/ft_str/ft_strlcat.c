/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:58:16 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/20 18:00:30 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		size_extra;
	size_t		size_dest;
	char		*buffer_dest;
	const char	*buffer_src;

	size_extra = size;
	buffer_dest = dest;
	buffer_src = src;
	while (*buffer_dest && size_extra--)
		buffer_dest++;
	size_dest = buffer_dest - dest;
	size_extra = size - size_dest;
	if (size_extra == 0)
		return (size_dest + ft_strlen(buffer_src));
	while (*buffer_src && size_extra > 1)
	{
		*buffer_dest = *buffer_src;
		buffer_dest++;
		buffer_src++;
		size_extra--;
	}
	*buffer_dest = '\0';
	return (size_dest + ft_strlen(src));
}
