/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:57:04 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 12:57:05 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>

void	init_exec_table(t_exec_table *exec_table)
{
	exec_table->exec_modes[NODE_COMMAND] = exec_command;
	exec_table->exec_modes[NODE_PIPE] = exec_pipe;
	exec_table->exec_modes[NODE_REDIRECTION] = exec_redir;
	exec_table->exec_modes[NODE_AND] = exec_and;
	exec_table->exec_modes[NODE_OR] = exec_or;
}
