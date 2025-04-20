/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:24:58 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/20 21:24:59 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executioner.h"
#include "ast_mock.h"
#include "utils.h"

int	shift_empty_args_left(t_anode *node)
{
	int	shift_count;
	int	i;

	if (!node || !node->args || !node->args[0])
		return (0);
	shift_count = 0;
	while (node->args[shift_count] && node->args[shift_count][0] == '\0')
		shift_count++;
	if (shift_count == 0 || !node->args[shift_count])
		return (0);
	i = -1;
	while (++i < shift_count)
		safe_free((void **)&node->args[i]);
	i = 0;
	while (node->args[i + shift_count])
	{
		node->args[i] = node->args[i + shift_count];
		i++;
	}
	node->args[i] = NULL;
	return (shift_count);
}
