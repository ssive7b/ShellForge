/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:43:22 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 19:43:23 by sstoev           ###   ########.fr       */
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
#include <fcntl.h>

void	setup_redirections(t_ast_node *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	else
		close(node->fd_in);
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
}

pid_t	fork_and_execute_child(t_tty *sh, t_ast_node *node)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		setup_redirections(node);
		execve(node->cmd_pathname, node->args, sh->envp);
		perror("execve");
		exit(127);
	}
	return (cpid);
}

void	wait_for_child(pid_t cpid, int *exit_status) // add some more robust handling later, e.g. WIFSIGNALED, WIFSTOPPED, WIFCONTINUED, etc.
{
	int	status;

	if (waitpid(cpid, &status, 0) == -1)
	{
		perror("waitpid");
		return ;
	}
	if (WIFEXITED(status))
    	*exit_status = WEXITSTATUS(status);
 	else
    	*exit_status = 1;
}

int	open_redirection_flle(const char *file_name, t_redir_type redir_type) // add some better handling of fds, i.e. proper handling of errors on opening/access, etc.
{
	int	fd;

	if (redir_type == REDIR_INPUT)	// populate the open_flags variable in the redir struct later
		fd = open(file_name, O_RDONLY);
	else if (redir_type == REDIR_OUTPUT)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == REDIR_APPEND)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}