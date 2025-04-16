/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:45:40 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/24 10:45:42 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"

static int	is_valid_n_flag(char *arg) // echo needs to be able to handle "echo -n -nnn -nn [char *]" types of cases
{
	size_t	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[++i])
	{
		if (arg[1] != 'n')
			return (0);
	}
	return (1);
}

void	exec_echo(t_anode *node)
{
	size_t	i;
	int		include_new_line;

	i = 1;
	include_new_line = 1;
	while (node->args[i] && is_valid_n_flag(node->args[i]))
	{
		include_new_line = 0;
		i++;
	}
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], node->fd_out);
		if (node->args[i+1])
			ft_putstr_fd(" ", node->fd_out);
		i++;
	}
	if (include_new_line)
		ft_putstr_fd("\n", node->fd_out);
}
