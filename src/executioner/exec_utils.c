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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <error.h>
#include <fcntl.h>
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"

static bool	validate_redir_file(t_shell *sh, const char *file_name, t_redir_type e_redir_type);

pid_t	fork_external_command(t_shell *sh, t_ast_node *node)
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
		display_error(sh);
		exit(127);
	}
	return (cpid);
}

bool	resolve_command_path(t_shell *sh, t_ast_node *node)
{
	if (!node->cmd_pathname && !is_builtin(node->args[0]))
	{
		sh->current_cmd = node->args[0];
		node->cmd_pathname = find_exec_pathname(sh, sh->env_list, node->args[0]);
		if (!node->cmd_pathname)
		{
			if (!sh->err_msg)
				set_error(sh, 127, "command not found");
			display_error(sh);
			node->exit_status = sh->error_code;
			sh->current_cmd = NULL;
			return (false);
		}
		sh->current_cmd = NULL;
	}
	return (true);
}

void	setup_redirections(t_ast_node *node)
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
}

int	open_redirection_flle(t_shell *sh, const char *file_name, t_redir_type redir_type) // add some better handling of fds, i.e. proper handling of errors on opening/access, etc.
{
	int	fd;
	int	flags;

	if (!validate_redir_file(sh, file_name, redir_type))
		return (-1);
	if (redir_type == REDIR_INPUT)	// populate the open_flags variable in the redir struct later
		flags = O_RDONLY;
	else if (redir_type == REDIR_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir_type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (-1);
	fd = open(file_name, flags, 0644);
	if (fd == -1)
	{
		ft_printf("bad bad bad\n");
		sh->current_cmd = (char *)file_name;
		set_error(sh, 1, strerror(errno));
		display_error(sh);
		sh->current_cmd = NULL;
	}
	return (fd);
}

static bool	validate_redir_file(t_shell *sh, const char *file_name, t_redir_type e_redir_type)
{
	if (!file_name)
	{
		set_error(sh, 1, "No filename provided for redirection");
		return (false);
	}
	if (e_redir_type == REDIR_INPUT && access(file_name, F_OK) == -1)
	{
		sh->current_cmd = (char *)file_name;
		set_error(sh, 1, "No such file or directory");
		display_error(sh);
		sh->current_cmd = NULL;
		return (false);
	}
	if ((e_redir_type == REDIR_OUTPUT || e_redir_type == REDIR_APPEND)
		&& access(file_name, F_OK) == 0 && access(file_name, W_OK) == -1)
	{
		sh->current_cmd = (char *)file_name;
		set_error(sh, 1, "Permission denied");
		display_error(sh);
		sh->current_cmd = NULL;
		return (false);
	}
	return (true);
}