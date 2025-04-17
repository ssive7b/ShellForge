/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 03:07:57 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/17 15:16:28 by sstoev           ###   ########.fr       */
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

void	setup_pipe_redirs(t_anode *cmd_node, int pipefd[2], int is_wr)
{
	if (is_wr)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		cmd_node->fd_out = STDOUT_FILENO;
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		cmd_node->fd_in = STDIN_FILENO;
	}
}

bool	create_pipe(t_shell *sh, t_anode *node, int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		set_error(sh, 1, strerror(errno));
		display_error(sh);
		return (false);
	}
	node->left->fd_out = pipefd[1];
	node->right->fd_in = pipefd[0];
	return (true);
}

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}
