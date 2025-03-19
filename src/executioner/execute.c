/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:38:18 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/18 19:38:20 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>

void	ft_execute(t_tty *minish, t_ast_node *ast_node)
{
	int		fd[2];
	pid_t	pid;

	if (ft_is_builtin(ast_node->cmd_name))
	{
		return ;
	}
	else
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
		{
			close(fd[0]);
			close(fd[1]);
			return ;
		}
		else if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve();
		}
	}

}