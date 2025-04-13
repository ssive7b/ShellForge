/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:55:57 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/12 23:57:29 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"

int	ft_is_unquoted_char(const char c)
{
	return (!ft_is_meta_char(c)
		&& !ft_is_quote(c)
		&& !ft_is_whitespace(c)
		&& c != '\0');
}

int	ft_find_char(const char *str, char char_to_find)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == char_to_find)
			return (i);
		i++;
	}
	return (-1);
}
