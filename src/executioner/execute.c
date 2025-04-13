/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:38:18 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:53:54 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_astree(t_shell *sh, t_ast_node *cmd_node)
{
	t_exec_table	exec_table;

	init_exec_table(&exec_table);
	if (!cmd_node)
		return ;
	if (cmd_node->type < NODE_TYPES_COUNT)
		exec_table.exec_modes[cmd_node->type](sh, cmd_node);
}
