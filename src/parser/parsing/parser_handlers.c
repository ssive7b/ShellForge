/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:26:08 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 20:30:37 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

static bool	parse_command_arguments(t_lexer *lexer, t_ast_node *cmd);

bool	handle_operator_precedence(t_lexer *lexer, t_ast_stack **op,
		t_ast_stack **operand)
{
	t_node_type	current_op_type;
	t_ast_node	*op_node;

	current_op_type = get_ast_node_type_from_token(lexer->tokens->type);
	while (*op
		&& op_precedence((*op)->node->type) >= op_precedence(current_op_type))
	{
		if (!process_operator(op, operand))
			return (false);
	}
	op_node = ast_new(current_op_type, lexer->tokens);
	if (!op_node)
		return (false);
	if (!push_ast_stack(op, op_node))
		return (false);
	advance_token(lexer);
	return (true);
}

void	*parse_cmd2(t_lexer *lexer)
{
	handle_parser_error(lexer, NULL, NULL, NULL);
	return (NULL);
}

// printf("received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
// printf("good- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*node;

	if (!lexer->tokens || !is_command_token(lexer->tokens->type))
	{
		ft_error_msg("Syntax error: Expected command");
		parse_cmd2(lexer);
	}
	node = ast_new(NODE_COMMAND, lexer->tokens);
	if (!node)
		parse_cmd2(lexer);
	if (!advance_token(lexer))
	{
		handle_parser_error(lexer, NULL, NULL, NULL);
		ft_error_msg("Syntax error: Couldn't advance tokens");
		return (NULL);
	}
	if (!parse_command_arguments(lexer, node))
	{
		handle_parser_error(lexer, NULL, NULL, &node);
		return (NULL);
	}
	return (node);
}

t_ast_node	*parse_parenthesized_expression(t_lexer *lexer,
		t_ast_stack **operator_stack, t_ast_stack **operand_stack)
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

// printf("cmd_args- received: %d %s\n", lexer->tokens->type,
//	lexer->tokens->value);
// printf("cmd_args- received: %d %s\n", lexer->tokens->type,
//	lexer->tokens->value);
static bool	parse_command_arguments(t_lexer *lexer, t_ast_node *cmd)
{
	skip_delims(lexer);
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
