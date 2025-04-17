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

#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <error.h>

void	exec_ast(t_shell *sh, t_anode *cmd_node)
{
	t_exec_table	exec_table;

	init_exec_table(&exec_table);
	if (!cmd_node)
		return ;
	if (cmd_node->type < NODE_TYPES_COUNT)
		exec_table.exec_modes[cmd_node->type](sh, cmd_node);
}
