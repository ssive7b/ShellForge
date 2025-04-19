/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:21:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/03 01:55:04 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "parser.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	op_precedence(t_ntype type)
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

int	stack_push(t_stack **stack, t_anode *node)
{
	t_stack	*new_node;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return (0);
	new_node->node = node;
	new_node->next = *stack;
	*stack = new_node;
	return (1);
}

t_anode	*stack_pop(t_stack **stack)
{
	t_stack	*current;
	t_anode	*node;

	current = *stack;
	if (current == NULL)
		return (NULL);
	node = current->node;
	*stack = current->next;
	safe_free((void **)&current);
	return (node);
}

bool	apply_op(t_stack **operator_stack, t_stack **operand_stack)
{
	t_anode	*op_node;
	t_anode	*right_operand;
	t_anode	*left_operand;

	if (!operator_stack || !(*operator_stack) || !operand_stack)
		return (false);
	if (!*operand_stack || !(*operand_stack)->next)
	{
		ft_error_msg("Error: Not enough operands for operator");
		return (false);
	}
	op_node = stack_pop(operator_stack);
	if (!op_node)
		return (false);
	right_operand = stack_pop(operand_stack);
	left_operand = stack_pop(operand_stack);
	op_node->right = right_operand;
	op_node->left = left_operand;
	stack_push(operand_stack, op_node);
	return (true);
}

t_ntype	tok_to_node(t_token_type type)
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
