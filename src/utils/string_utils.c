/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:59:12 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 22:02:25 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"
#include "utils.h"

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

char	*ft_strjoin_multiple(char **str_list, size_t num_strings)
{
	char	*result;
	size_t	len_total;
	size_t	len_result;
	size_t	i;

	if (!str_list || num_strings == 0)
		return (NULL);
	i = -1;
	len_total = 0;
	while (++i < num_strings)
		len_total += ft_strlen(str_list[i]);
	if (len_total == 0)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (len_total + 1));
	if (!result)
		return (NULL);
	i = -1;
	len_result = 0;
	while (++i < num_strings && str_list[i])
		len_result += ft_strlcpy(&result[len_result], str_list[i], len_total);
	return (result);
}

int	ft_skip_whitespaces(const char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	return (i);
}

int	ft_is_escaped(const char *str, size_t idx)
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

int	ft_char_qadjusted(const char *str, char char_to_find)
{
	size_t	idx;

	if (!str || !*str)
		return (-1);
	idx = 0;
	while (str[idx] && (str[idx] != char_to_find || ft_is_escaped(str, idx)))
		idx++;
	if (!str[idx])
		idx--;
	return (idx);
}
