/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:10:36 by sstoev            #+#    #+#             */
/*   Updated: 2024/09/23 22:10:58 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new_src;
	size_t	len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	new_src = (char *)malloc(sizeof(char) * (len_src + 1));
	if (!new_src)
		return (NULL);
	while (i < len_src)
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[i] = '\0';
	return (new_src);
}
/*
#include <string.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	char 	*duplicate;
	char	*result;
	

	if (argc != 2)
		return (0);
	duplicate = NULL;
	result = ft_strdup(duplicate);
	printf("'%s'\n", result);
	duplicate = ft_strdup(argv[1]);
	if (duplicate)
	{
		printf("Original value:%s\n",argv[1]);
		printf("Duplicated value:%s\n",duplicate);
		free(duplicate);
	}
	else
		printf("Failed to allocate memory.\n");
	return (0);
}
*/
