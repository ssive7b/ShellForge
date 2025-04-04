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

#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>

void	*execute_command(t_shell *sh, t_ast_node *node)
{
	pid_t	cpid;

	if (!node)
		return (NULL);
	if (is_builtin(node->args[0]))
	{
		exec_builtin(node);
		return (NULL);
	}
	else
	{
		cpid = fork_and_execute_child(sh, node);
		if (cpid == -1)
			return (NULL);
		node->pid = cpid;
		wait_for_child(cpid, &node->exit_status);
	}
	return (NULL);
}

void	*execute_pipe(t_shell *sh, t_ast_node *node)
{
	int pipefd[2];

	if (!node)
		return (NULL);
	if (pipe(pipefd) == -1)
	{
		ft_error_msg("Execution error: pipe");
		return (NULL);
	}
	node->left->fd_out = pipefd[1];
	node->right->fd_in = pipefd[0];
	exec_astree(sh, node->left);
	close(pipefd[1]);
	exec_astree(sh, node->right);
	close(pipefd[0]);
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
		fd = open_redirection_flle(node->redir->file_name, node->redir->type);
	if (fd == -1)
	{
		ft_error_msg("Execution error: redirection");
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
		exec_astree(sh, node->right);
	return (NULL);
}

void	*execute_or(t_shell *sh, t_ast_node *node)
{
	if (!node)
		return (NULL);
	exec_astree(sh, node->left);
	if (node->left->exit_status != 0)
		exec_astree(sh, node->right);
	return (NULL);
}