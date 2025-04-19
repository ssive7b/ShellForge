/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 03:07:57 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/17 15:16:20 by sstoev           ###   ########.fr       */
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
#include "signal_handlers.h"

pid_t	fork_pipe_cmd(t_shell *sh, t_anode *cmd_node, int pipefd[2], int is_wr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		set_error(sh, 1, strerror(errno));
		display_error(sh);
		return (-1);
	}
	if (pid == 0)
	{
		restore_default_signals();
		setup_pipe_redirs(cmd_node, pipefd, is_wr);
		exec_ast(sh, cmd_node);
		exit(cmd_node->exit_status);
	}
	return (pid);
}

void	handle_fork_err(pid_t lpid, int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (lpid > 0)
	{
		kill(lpid, SIGTERM);
		waitpid(lpid, NULL, 0);
	}
}

void	wait_pipeline(t_shell *sh, pid_t lpid, pid_t rpid, int *exit_status)
{
	int	status;

	setup_parent_signals();
	wait_child(sh, lpid, &status);
	wait_child(sh, rpid, exit_status);
	sh->last_exit_code = *exit_status;
	setup_interactive_signals();
}

void	wait_child(t_shell *sh, pid_t cpid, int *exit_status)
{
	int	status;

	if (waitpid(cpid, &status, 0) == -1)
	{
		set_error(sh, 1, strerror(errno));
		display_error(sh);
		*exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_child_signal(WTERMSIG(status), exit_status);
	else
		*exit_status = 1;
}
