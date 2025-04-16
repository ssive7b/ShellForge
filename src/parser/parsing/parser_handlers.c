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

static bool	parse_command_arguments(t_lexer *lexer, t_anode *cmd);

bool	handle_op_prec(t_lexer *lexer, t_stack **operator_stack, t_stack **operand_stack)
{
	t_ntype	current_op_type;
	t_anode	*op_node;

	current_op_type = tok_to_node(lexer->tokens->type);
	while (*operator_stack && op_precedence((*operator_stack)->node->type) >= op_precedence(current_op_type))
	{
		if (!apply_op(operator_stack, operand_stack))
			return (false);
	}
	op_node = node_new(current_op_type, lexer->tokens);
	if (!op_node)
		return (false);
	if (!stack_push(operator_stack, op_node))
		return (false);
	next_token(lexer);
	return (true);
}

t_anode	*parse_cmd(t_lexer *lexer)
{
	t_anode	*node;

	if (!lexer->tokens || !is_cmd_tok(lexer->tokens->type))
	{
		ft_error_msg("Syntax error: Expected command");
		// printf("received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
		parse_err(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	// printf("good- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	node = node_new(NODE_COMMAND, lexer->tokens);
	if (!node)
	{
		parse_err(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	if (!next_token(lexer))
	{
		parse_err(lexer, NULL, NULL, NULL);
		ft_error_msg("Syntax error: Couldn't advance tokens");
		return (NULL);
	}
	if (!parse_command_arguments(lexer, node))
	{
		parse_err(lexer, NULL, NULL, &node);
		return (NULL);
	}
	return (node);
}

t_anode	*parse_paren_expr(t_lexer *lexer, t_stack **operator_stack, t_stack **operand_stack)
{
	t_anode	*expr;

	next_token(lexer);
	expr = parse_expr(lexer, operator_stack, operand_stack);
	if (!expr)
	{
		parse_err(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	if (!lexer->tokens || lexer->tokens->type != TOKEN_RPAREN)
	{
		ft_error_msg("Error: Missing closing parenthesis");
		parse_err(lexer, NULL, NULL, &expr);
		return (NULL);
	}
	next_token(lexer);
	return (expr);
}

static bool	parse_command_arguments(t_lexer *lexer, t_anode *cmd)
{
	skip_delims(lexer);
	// printf("cmd_args- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	while (lexer->tokens && is_arg_tok(lexer->tokens->type))
	{
		if (!add_arg(cmd, lexer->tokens->value))
			return (false);
		next_token(lexer);
		while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
			next_token(lexer);
	}
	// printf("cmd_args- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	return (true);
}
