/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:00:22 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 20:12:58 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"
#include "utils.h"

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// some rethinking might be needed,
// because var names cannot begin with a numeric
char	*extract_var_name(const char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	if (!str || !i || !is_valid_var_char(str[*i]))
		return (NULL);
	start = *i;
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	len = *i - start;
	var_name = ft_substr(str, start, len);
	return (var_name);
}
