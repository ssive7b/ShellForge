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

pid_t	execute_left_command(t_shell *sh, t_ast_node *left_node)
{
	pid_t	pid;

	pid = fork_and_execute_child(sh, left_node);
	if (pid == -1)
		set_error(sh, 1, "for error for left command");
	return (pid);
}

pid_t	execute_right_command(t_shell *sh, t_ast_node *right_node)
{
	pid_t	pid;

	pid = fork_and_execute_child(sh, right_node);
	if (pid == -1)
		set_error(sh, 1, "fork error for right command");
	return (pid);
}

pid_t	fork_and_execute_child(t_shell *sh, t_ast_node *node)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		set_error(sh, 1, "fork error");
		display_error(sh);
		return (-1);
	}
	if (cpid == 0)
	{
		setup_redirections(node);
		execve(node->cmd_pathname, node->args, sh->envp);
		set_error(sh, 127, strerror(errno));
		exit(127);
	}
	return (cpid);
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