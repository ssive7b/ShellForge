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

#include "ast_mock.h"
#include "minishell.h"
#include "executioner.h"
#include "env_utils.h"

int	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	return (0);
}


void	exec_builtin(t_anode *cmd_node)
{
	if (ft_strcmp(cmd_node->args[0], "echo") == 0)
		exec_echo(cmd_node);
	else if (ft_strcmp(cmd_node->args[0], "env") == 0)
		exec_env(cmd_node, *get_env());
	else if (ft_strcmp(cmd_node->args[0], "exit") == 0)
		exec_exit(cmd_node);
	else if (ft_strcmp(cmd_node->args[0], "pwd") == 0)
		exec_pwd(cmd_node);
	else if (ft_strcmp(cmd_node->args[0], "unset") == 0)
		exec_unset(cmd_node);
	else if (ft_strcmp(cmd_node->args[0], "export") == 0)
		exec_export(cmd_node);
	else if (ft_strcmp(cmd_node->args[0], "cd") == 0)
		exec_cd(cmd_node);
}
