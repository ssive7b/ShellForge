/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:21:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:12:28 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int	get_operator_precedence(t_node_type type)
{
	if (type == NODE_LPAREN || type == NODE_RPAREN)
		return (3);
	else if (type == NODE_REDIRECTION)
		return (2);
	else if (type == NODE_PIPE)
		return (1);
	else if (type == NODE_AND || type == NODE_OR)
		return (0);
	return (-1);
}

int	push_ast_stack(t_ast_stack **stack, t_ast_node *node)
{
	t_ast_stack	*new_node;

	new_node = malloc(sizeof(t_ast_stack));
	if (!new_node)
		return (0);
	new_node->node = node;
	new_node->next = *stack;
	*stack = new_node;
	return (1);
}

t_ast_node	*pop_ast_stack(t_ast_stack **stack)
{
	t_ast_stack	*current;
	t_ast_node	*node;

	current = *stack;
	if (current == NULL)
		return (NULL);
	node = current->node;
	*stack = current->next;
	safe_free((void **)&current);
	return (node);
}

bool	process_operator(t_ast_stack **operator_stack,
		t_ast_stack **operand_stack)
{
	t_ast_node	*op_node;
	t_ast_node	*right_operand;
	t_ast_node	*left_operand;

	if (!operator_stack || !(*operator_stack) || !operand_stack)
		return (false);
	if (!*operand_stack || !(*operand_stack)->next)
	{
		ft_error_msg("Error: Not enough operands for operator");
		return (false);
	}
	op_node = pop_ast_stack(operator_stack);
	if (!op_node)
		return (false);
	right_operand = pop_ast_stack(operand_stack);
	left_operand = pop_ast_stack(operand_stack);
	op_node->right = right_operand;
	op_node->left = left_operand;
	push_ast_stack(operand_stack, op_node);
	return (true);
}

t_node_type	get_ast_node_type_from_token(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (type == TOKEN_OR)
		return (NODE_OR);
	if (type == TOKEN_AND)
		return (NODE_AND);
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC)
		return (NODE_REDIRECTION);
	return (NODE_COMMAND);
}
