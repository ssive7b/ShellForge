/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:39:08 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/24 12:39:10 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"
#include "char_designation.h"
#include "utils.h"

static bool	is_valid_number(char *str)
{
	while (is_whitespace(*str))
		str++;
	if (*str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0' || !ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	while (is_whitespace(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

void	exec_exit(t_anode *node)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (node->args[1])
	{
		if (!is_valid_number(node->args[1]))
		{
			node->exit_status = 255;
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(node->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
		if (node->args[2])
		{
			node->exit_status = 1;
			shell_error("exit", "too many arguments");
			return ;
		}
		node->exit_status = ft_atoi(node->args[1]) % 256;
		if (node->exit_status < 0)
			node->exit_status += 256;
	}
	exit(node->exit_status);
}
