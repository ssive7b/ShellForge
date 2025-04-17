/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:59:12 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/14 00:59:13 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "char_designation.h"

bool	safe_strjoin(char **dest, const char *source)
{
	char	*old_str;
	char	*new_str;

	if (!dest || !*dest || !source)
		return (false);
	old_str = *dest;
	new_str = ft_strjoin(old_str, source);
	if (!new_str)
		return (false);
	safe_free((void **)dest);
	*dest = new_str;
	return (true);
}

int	skip_whitesps(const char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && is_whitespace(str[i]))
		i++;
	return (i);
}

int	is_esc(const char *str, size_t idx)
{
	if (str[idx] == '\0')
		return (0);
	if (idx == 0)
		return (0);
	if (str[idx - 1] == '\\')
	{
		if (idx >= 2 && str[idx - 2] == '\\')
			return (0);
		return (1);
	}
	return (0);
}

int	find_char_qadj(const char *str, char char_to_find)
{
	size_t	idx;

	if (!str || !*str)
		return (-1);
	idx = 0;
	while (str[idx] && (str[idx] != char_to_find || is_esc(str, idx)))
		idx++;
	if (!str[idx])
		idx--;
	return (idx);
}

int	find_char(const char *str, char char_to_find)
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
