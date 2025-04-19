/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multiple.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:40:53 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 23:40:54 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
