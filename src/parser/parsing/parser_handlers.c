/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:26:08 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 00:26:09 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

static bool	parse_command_arguments(t_lexer *lexer, t_ast_node *cmd);

bool	handle_operator_precedence(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_node_type	current_op_type;
	t_ast_node	*op_node;

	current_op_type = get_ast_node_type_from_token(lexer->tokens->type);
	while (*operator_stack && get_operator_precedence((*operator_stack)->node->type) >= get_operator_precedence(current_op_type))
	{
		if (!process_operator(operator_stack, operand_stack))
			return (false);
	}
	op_node = ast_new(current_op_type, lexer->tokens);
	if (!op_node)
		return (false);
	if (!push_ast_stack(operator_stack, op_node))
		return (false);
	advance_token(lexer);
	return (true);
}

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*node;

	if (!lexer->tokens || !is_command_token(lexer->tokens->type))
	{
		ft_error_msg("Syntax error: Expected command");
		handle_parser_error(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	node = ast_new(NODE_COMMAND, lexer->tokens);
	if (!node)
	{
		handle_parser_error(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	advance_token(lexer);
	if (!parse_command_arguments(lexer, node))
	{
		handle_parser_error(lexer, NULL, NULL, &node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*parse_parenthesized_expression(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*expr;

	advance_token(lexer);
	expr = parse_expression(lexer, operator_stack, operand_stack);
	if (!expr)
	{
		handle_parser_error(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	if (!lexer->tokens || lexer->tokens->type != TOKEN_RPAREN)
	{
		ft_error_msg("Error: Missing closing parenthesis");
		handle_parser_error(lexer, NULL, NULL, &expr);
		return (NULL);
	}
	advance_token(lexer);
	return (expr);
}

static bool	parse_command_arguments(t_lexer *lexer, t_ast_node *cmd)
{
	while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
		advance_token(lexer);
	while (lexer->tokens && is_argument_token(lexer->tokens->type))
	{
		if (!add_argument_to_node(cmd, lexer->tokens->value))
			return (false);
		advance_token(lexer);
		while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
			advance_token(lexer);
	}
	return (true);
}
