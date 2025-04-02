/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:21:13 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/20 15:21:14 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_2d_array(char ***array, int n)
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