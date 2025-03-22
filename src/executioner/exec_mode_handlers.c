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
		return (NULL);
	}
	else
	{
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			return (NULL);
		}
		if (cpid == 0)
		{
			if (node->fd_in != STDIN_FILENO)
			{
				dup2(node->fd_in, STDIN_FILENO);
				close(node->fd_in);
			}
			if (node->fd_out != STDOUT_FILENO)
			{
				dup2(node->fd_out, STDOUT_FILENO);
				close(node->fd_out);
			}
			execve(node->cmd_pathname, node->args, sh->envp);
			perror("execve");
			return (NULL);
		}
		else
		{
			close(node->fd_in);
			close(node->fd_out);
			if (waitpid(cpid, &node->exit_status, 0) == -1)
			{
				perror("waitpid");
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	*execute_pipe(t_tty *sh, t_ast_node *node)
{
	(void)sh;
	(void)node;
	return (NULL);
}

void	*execute_redirection(t_tty *sh, t_ast_node *node)
{
	(void)sh;
	(void)node;
	return (NULL);
}

void	*execute_and(t_tty *sh, t_ast_node *node)
{
	(void)sh;
	(void)node;
	return (NULL);
}

void	*execute_or(t_tty *sh, t_ast_node *node)
{
	(void)sh;
	(void)node;
	return (NULL);
}