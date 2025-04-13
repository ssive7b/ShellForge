/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:38:18 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 20:25:55 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	*execute_and(t_shell *sh, t_ast_node *node)
{
	if (!node)
		return (NULL);
	exec_astree(sh, node->left);
	if (node->left->exit_status == 0)
	{
		exec_astree(sh, node->right);
		node->exit_status = node->right->exit_status;
	}
	else
		node->exit_status = node->left->exit_status;
	sh->last_exit_code = node->exit_status;
	return (NULL);
}

void	*execute_or(t_shell *sh, t_ast_node *node)
{
	if (!node)
		return (NULL);
	exec_astree(sh, node->left);
	if (node->left->exit_status != 0)
	{
		exec_astree(sh, node->right);
		node->exit_status = node->right->exit_status;
	}
	else
		node->exit_status = node->left->exit_status;
	sh->last_exit_code = node->exit_status;
	return (NULL);
}

void	exec_astree(t_shell *sh, t_ast_node *cmd_node)
{
	t_exec_table	exec_table;

	init_exec_table(&exec_table);
	if (!cmd_node)
		return ;
	if (cmd_node->type < NODE_TYPES_COUNT)
		exec_table.exec_modes[cmd_node->type](sh, cmd_node);
}
