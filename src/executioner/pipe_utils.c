/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 03:07:57 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/06 03:07:58 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <error.h>
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"

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
	if (node->left->type == NODE_COMMAND && !resolve_command_path(sh, node->left))
		return (false);
	if (node->right->type == NODE_COMMAND && !resolve_command_path(sh, node->right))
		return (false);
	return (true);
}

pid_t	fork_pipe_process(t_shell *sh, t_ast_node *cmd_node, int pipefd[2], int is_writer)
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

void	execute_pipe_child(t_shell *sh, t_ast_node *cmd_node, int pipefd[2], int is_writer)
{
	if (is_writer)
	{
		close(pipefd[0]);
		setup_redirections(cmd_node);
	}
	else
	{
		close(pipefd[1]);
		setup_redirections(cmd_node);
	}
	if (cmd_node->type == NODE_COMMAND && cmd_node->cmd_pathname)
		execve(cmd_node->cmd_pathname, cmd_node->args, sh->envp);
	else
		exec_astree(sh, cmd_node);
	if (cmd_node->exit_status)
		exit(cmd_node->exit_status);
	else
		exit(127);
}

void	handle_fork_error(pid_t left_pid, int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (left_pid > 0)
	{
		kill(left_pid, SIGTERM);
		waitpid(left_pid, NULL, 0);
	}
}

void	wait_for_pipeline(t_shell *sh, pid_t left_pid, pid_t right_pid, int *exit_status)
{
	int	status;

	wait_for_child(sh, left_pid, &status);
	wait_for_child(sh, right_pid, exit_status);
	sh->last_exit_code = *exit_status;
}

void	close_pipe(int	pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}


void	wait_for_child(t_shell *sh, pid_t cpid, int *exit_status) // add some more robust handling later, e.g. WIFSIGNALED, WIFSTOPPED, WIFCONTINUED, etc.
{
	int	status;

	if (waitpid(cpid, &status, 0) == -1)
	{
		set_error(sh, 1, strerror(errno));
		display_error(sh);
		return ;
	}
	if (WIFEXITED(status))
    	*exit_status = WEXITSTATUS(status);
 	else
    	*exit_status = 1;
}