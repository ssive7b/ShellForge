/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mode_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:24:34 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 13:24:35 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"

void	*execute_command(t_shell *sh, t_ast_node *node)
{
	pid_t	cpid;

	if (!node || !node->args || !node->args[0])
		return (NULL);
	if (is_builtin(node->args[0]))
	{
		exec_builtin(node);
		return (NULL);
	}
	if (!resolve_command_path(sh, node))
		return (NULL);
	cpid = fork_external_command(sh, node);
	if (cpid == -1)
		return (NULL);
	node->pid = cpid;
	wait_for_child(sh, cpid, &node->exit_status);
	sh->last_exit_code = node->exit_status;
	return (NULL);
}

void	*execute_pipe(t_shell *sh, t_ast_node *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node || !create_pipe(sh, node, pipefd))
		return (NULL);
	if (!prepare_pipe_commands(sh, node))
	{
		close_pipe(pipefd);
		return (NULL);
	}
	left_pid = fork_pipe_process(sh, node->left, pipefd, 1);
	if (left_pid == -1)
	{
		close_pipe(pipefd);
		return (NULL);
	}
	right_pid = fork_pipe_process(sh, node->right, pipefd, 0);
	if (right_pid == -1)
	{
		handle_fork_error(left_pid, pipefd);
		return (NULL);
	}
	close_pipe(pipefd);
	wait_for_pipeline(sh, left_pid, right_pid, &node->exit_status);
	return (NULL);
}

void	*execute_redirection(t_shell *sh, t_ast_node *node) // to-do: allow for HEREDOC in the below implementation
{
	int	fd;

	if (!node || !node->redir)
		return (NULL);
	if (node->redir->type == REDIR_HEREDOC)
		fd = get_heredoc_fd(node->redir);
	else
		fd = open_redirection_flle(sh, node->redir->file_name, node->redir->type);
	if (fd == -1)
	{
		node->exit_status = 1;
		return (NULL);
	}
	if (node->redir->type == REDIR_INPUT || node->redir->type == REDIR_HEREDOC)
		node->left->fd_in = fd;
	else
		node->left->fd_out = fd;
	exec_astree(sh, node->left);
	close(fd);
	return (NULL);
}

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