/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:43:57 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 23:44:00 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_2d_array(char ***array, int n)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((n == -1 || i < n) && (*array)[i])
	{
		safe_free((void **)&(*array)[i]);
		i++;
	}
	safe_free((void **)(*array));
	*array = NULL;
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**allocate_args_array(int size)
{
	char	**new_array;

	new_array = malloc((size + 1) * sizeof(char *));
	if (!new_array)
	{
		ft_error_msg("Error: Memory allocation failed while allocating array");
		return (NULL);
	}
	new_array[size] = NULL;
	return (new_array);
}

bool	copy_args(char **dst, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i] = safe_strdup(src[i]);
		if (!dst[i])
		{
			free_2d_array(&dst, i);
			return (false);
		}
		i++;
	}
	return (true);
}
