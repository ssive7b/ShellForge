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

#include "utils.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*safe_strdup(const char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
		ft_error_msg("Error: Memory allocation failed in strdup()");
	return (dup);
}