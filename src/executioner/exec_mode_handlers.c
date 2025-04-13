/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mode_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:24:34 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 20:28:12 by cschnath         ###   ########.fr       */
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

void	*execute_command(t_shell *sh, t_ast_node *node)
{
	pid_t	cpid;

	if (!node || !node->args || !node->args[0])
		return (NULL);
	if (node->redirections)
		execute_redirection(sh, node);
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
		return (close_pipe(pipefd), NULL);
	left_pid = fork_pipe_process(sh, node->left, pipefd, 1);
	if (left_pid == -1)
		return (close_pipe(pipefd), NULL);
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

// to-do: allow for HEREDOC in the below implementation
// exec_astree(sh, node);
// Handles a single redirection
static int	process_single_redirection(t_shell *sh, t_ast_node *node,
		t_redir *redir)
{
	int	fd;

	printf("Processing redirection: type=%d, file=%s\n", redir->type,
		redir->file_name);
	if (redir->type == REDIR_HEREDOC)
		fd = get_heredoc_fd(redir);
	else
		fd = open_redirection_flle(sh, redir->file_name, redir->type);
	if (fd == -1)
	{
		node->exit_status = 1;
		return (-1);
	}
	if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
		node->fd_in = fd;
	else
		node->fd_out = fd;
	return (0);
}

// Iterates through the list of redirections
void	*execute_redirection(t_shell *sh, t_ast_node *node)
{
	t_list	*redir_list;
	t_redir	*redir;

	if (!node || !node->redirections)
		return (NULL);
	redir_list = node->redirections;
	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		if (process_single_redirection(sh, node, redir) == -1)
		{
			clear_redirections(&redir_list);
			return (NULL);
		}
		redir_list = redir_list->next;
	}
	clear_redirections(&redir_list);
	return (NULL);
}
