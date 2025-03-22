/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:52:01 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/18 19:52:02 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", 5) == 0)
		return (1);
	return (0);
}

/*
void	ft_exec_builtin(t_ast_node *cmd_node)
{
	if (ft_strncmp(cmd_node->cmd_name, "cd", 2) == 0)
		ft_exec_cd(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "echo", 4) == 0)
		ft_exec_echo(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "env", 3) == 0)
		ft_exec_env(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "exit", 4) == 0)
		ft_exec_exit(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "export", 6) == 0)
		ft_exec_export(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "pwd", 3) == 0)
		exec_pwd(cmd_node);
	else if (ft_strncmp(cmd_node->cmd_name, "unset", 5) == 0)
		ft_exec_unset(cmd_node);
}
*/