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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>

void	*execute_command(t_tty *sh, t_ast_node *node)
{
	pid_t	cpid;

	if (!node)
		return (NULL);
	if (is_builtin(node->args[0]))
	{
		return (NULL);			// to be done: implement the logic for handling builtins
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

void	*execute_pipe(t_tty *sh, t_ast_node *node)
{
	int pipefd[2];

	if (!node)
		return (NULL);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
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

void	*execute_redirection(t_tty *sh, t_ast_node *node) // to-do: allow for HEREDOC in the below implementation
{
	int	fd;

	if (!node)
		return (NULL);
	fd = open_redirection_flle(node->redir->file_name, node->redir->type);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	if (node->redir->type == REDIR_INPUT)
		node->left->fd_in = fd;
	else
		node->left->fd_out = fd;
	exec_astree(sh, node->left);
	close(fd);
	return (NULL);
}

void	*execute_and(t_tty *sh, t_ast_node *node)
{
	if (!node)
		return (NULL);
	exec_astree(sh, node->left);
	if (node->left->exit_status == 0)
		exec_astree(sh, node->right);
	return (NULL);
}

void	*execute_or(t_tty *sh, t_ast_node *node)
{
	if (!node)
		return (NULL);
	exec_astree(sh, node->left);
	if (node->left->exit_status != 0)
		exec_astree(sh, node->right);
	return (NULL);
}