/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:43:46 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 19:44:17 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

bool	create_pipe(t_shell *sh, t_ast_node *node, int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		set_error(sh, 1, "pipe error");
		display_error(sh);
		return (false);
	}
	node->left->fd_out = pipefd[1];
	node->right->fd_in = pipefd[0];
	return (true);
}

bool	prepare_pipe_commands(t_shell *sh, t_ast_node *node)
{
	if (node->left->type == NODE_COMMAND && !resolve_command_path(sh,
			node->left))
		return (false);
	if (node->right->type == NODE_COMMAND && !resolve_command_path(sh,
			node->right))
		return (false);
	return (true);
}

pid_t	fork_pipe_process(t_shell *sh, t_ast_node *cmd_node, int pipefd[2],
		int is_writer)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		set_error(sh, 1, "fork error");
		display_error(sh);
		return (-1);
	}
	if (pid == 0)
		execute_pipe_child(sh, cmd_node, pipefd, is_writer);
	return (pid);
}
