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
#include "parser.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"

void	*exec_command(t_shell *sh, t_anode *node)
{
	pid_t	cpid;

	if (!node || !node->args || !node->args[0])
		return (update_exit_code(sh, node), NULL);
	if (node->redirections)
	{
		exec_redir(sh, node);
		if (!node->redirections)
			return (update_exit_code(sh, node), NULL);
	}
	if (is_builtin(node->args[0]))
	{
		exec_builtin(node);
		return (update_exit_code(sh, node), NULL);
	}
	if (!resolve_path(sh, node))
		return (update_exit_code(sh, node), NULL);
	cpid = fork_extern_cmd(sh, node);
	if (cpid == -1)
		return (update_exit_code(sh, node), NULL);
	node->pid = cpid;
	wait_child(sh, cpid, &node->exit_status);
	sh->last_exit_code = node->exit_status;
	return (update_exit_code(sh, node), NULL);
}

void	*exec_pipe(t_shell *sh, t_anode *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node || !create_pipe(sh, node, pipefd))
		return (NULL);
	left_pid = fork_pipe_cmd(sh, node->left, pipefd, 1);
	if (left_pid == -1)
	{
		close_pipe(pipefd);
		return (NULL);
	}
	right_pid = fork_pipe_cmd(sh, node->right, pipefd, 0);
	if (right_pid == -1)
	{
		handle_fork_err(left_pid, pipefd);
		return (NULL);
	}
	close_pipe(pipefd);
	wait_pipeline(sh, left_pid, right_pid, &node->exit_status);
	return (NULL);
}

void	*exec_redir(t_shell *sh, t_anode *node)
{
	t_list	*redir_list;
	t_redir	*redir;
	int		fd;

	if (!node || !node->redirections)
		return (NULL);
	redir_list = node->redirections;
	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		if (redir->type == REDIR_HEREDOC)
			fd = get_hdoc_fd(redir);
		else
			fd = open_redir_flle(sh, redir->file_name, redir->type);
		if (fd == -1)
		{
			node->exit_status = 1;
			clear_redirs(&(node->redirections));
			return (NULL);
		}
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			node->fd_in = fd;
		else
			node->fd_out = fd;
		redir_list = redir_list->next;
	}
	return (NULL);
}

void	*exec_and(t_shell *sh, t_anode *node)
{
	if (!node)
		return (NULL);
	exec_ast(sh, node->left);
	if (node->left->exit_status == 0)
	{
		exec_ast(sh, node->right);
		node->exit_status = node->right->exit_status;
	}
	else
		node->exit_status = node->left->exit_status;
	sh->last_exit_code = node->exit_status;
	return (NULL);
}

void	*exec_or(t_shell *sh, t_anode *node)
{
	if (!node)
		return (NULL);
	exec_ast(sh, node->left);
	if (node->left->exit_status != 0)
	{
		exec_ast(sh, node->right);
		node->exit_status = node->right->exit_status;
	}
	else
		node->exit_status = node->left->exit_status;
	sh->last_exit_code = node->exit_status;
	return (NULL);
}