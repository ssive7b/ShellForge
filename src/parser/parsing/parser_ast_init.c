/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:21:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/03 01:54:50 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "parser.h"
#include "lexer.h"
#include "env_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void	initialize_ast_node(t_anode *node, t_ntype type);
static bool	setup_command_node(t_anode *node, char *value);

t_anode	*node_new(t_ntype type, t_token *token)
{
	t_anode	*new;

	if (!token)
	{
		ft_error_msg("Error: node_new received NULL token");
		return (NULL);
	}
	new = malloc(sizeof(t_anode));
	if (!new)
		return (NULL);
	initialize_ast_node(new, type);
	if (type == NODE_COMMAND)
	{
		if (!setup_command_node(new, token->value))
		{
			ft_error_msg("Error: Memory allocation failed for args in node_new");
			node_free(&new);
			return (NULL);
		}
	}
	return (new);
}

static void	initialize_ast_node(t_anode *node, t_ntype type)
{
	if (!node)
		return ;
	node->type = type;
    node->cmd_pathname = NULL;
    node->args = NULL;
    node->pid = -1;
    node->fd_in = STDIN_FILENO;
    node->fd_out = STDOUT_FILENO;
    node->exit_status = 0;
    node->redirections = NULL;
    node->left = NULL;
    node->right = NULL;
}

static bool	setup_command_node(t_anode *node, char *value)
{
	node->cmd_pathname = NULL;
    node->args = malloc(2 * sizeof(char *));
    if (!node->args)
    {
		safe_free((void **)&node->cmd_pathname);
        return (false);
    }
    node->args[0] = ft_strdup(value);
	if (!node->args[0])
	{
		safe_free((void **)&node->args);
		safe_free((void **)&node->cmd_pathname);
		return (false);
	}
    node->args[1] = NULL;
	return (true);
}
