/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cleaners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:32:56 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 14:32:58 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

void	free_ast_node(t_ast_node **node)
{
	size_t	i;

	if (!node || !*node)
		return ;
	if ((*node)->left)
		free_ast_node(&(*node)->left);
	if ((*node)->right)
		free_ast_node(&(*node)->right);
	if ((*node)->type == NODE_COMMAND)
	{
		safe_free((void **)&(*node)->cmd_pathname);
		if ((*node)->args)
		{
			i = 0;
			while((*node)->args[i])
			{
				safe_free((void **)&(*node)->args[i]);
				i++;
			}
			safe_free((void **)&(*node)->args);
		}
	}
	if ((*node)->redir)
	{
		safe_free((void **)&(*node)->redir->file_name);
		safe_free((void **)&(*node)->redir->delimiter_heredoc);
		safe_free((void **)&(*node)->redir);
	}
	safe_free((void **)node);
}

void	free_ast_stack(t_ast_stack **stack)
{
	t_ast_stack	*current;
	t_ast_stack	*next;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		free_ast_node(&current->node);
		safe_free((void **)&current);
		current = next;
	}
	*stack = NULL;
}

void	cleanup_parser_state(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_ast_node **node)
{
	if (operand_stack)
		free_ast_stack(operator_stack);
	if (operand_stack)
		free_ast_stack(operand_stack);
	if (node && *node)
		free_ast_node(node);
}

void	handle_parser_error(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_ast_node **node)
{
	if (lexer)
		lexer->error = 1;
	if (operand_stack)
		free_ast_stack(operator_stack);
	if (operand_stack)
		free_ast_stack(operand_stack);
	if (node && *node)
		free_ast_node(node);
}