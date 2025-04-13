/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:25:50 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:41:01 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

t_ast_node	*parse_tokens(t_lexer *lexer)
{
	t_ast_stack	*operator_stack;
	t_ast_stack *operand_stack;
	t_ast_node	*result_expr;

	operator_stack = NULL;
	operand_stack = NULL;
	result_expr = parse_expression(lexer, &operator_stack, &operand_stack);
	if (!result_expr || lexer->tokens || lexer->error)
	{
		ft_error_msg("Error: Failed while parsing tokens");
		handle_parser_error(lexer, NULL, NULL, &result_expr);
		return (NULL);
	}
	free_ast_stack(&operator_stack);
	free_ast_stack(&operand_stack);
	return (result_expr);
}

t_ast_node	*parse_expression(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*first_operand;
	t_ast_node	*finalized_expression;

	first_operand = parse_command_with_redirects(lexer, operator_stack, operand_stack);
	if (!first_operand)
		return (NULL);
	if (!push_ast_stack(operand_stack, first_operand))
		return (NULL);
	// printf("parse_expr- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	if (!parse_infix_operators(lexer, operator_stack, operand_stack))
		return (NULL);
	finalized_expression = finalize_expression(operator_stack, operand_stack, lexer);
	return (finalized_expression);
}

bool	parse_infix_operators(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*next_operand;

	skip_delims(lexer);
	// printf("parse_infix- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	while (lexer->tokens && is_operator_token(lexer->tokens->type))
	{
		// printf("[inside loop] parse_infix- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
		if (!handle_operator_precedence(lexer, operator_stack, operand_stack))
			return (false);
		next_operand = parse_command_with_redirects(lexer, operator_stack, operand_stack);
		if (!next_operand)
			return (false);
		if (!push_ast_stack(operand_stack, next_operand))
			return (false);
	}
	return (true);
}

t_ast_node	*finalize_expression(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_lexer *lexer)
{
	t_ast_node	*result;

	while (*operator_stack)
	{
		if (!process_operator(operator_stack, operand_stack))
		{
			ft_error_msg("Error: Failed to process operator");
			handle_parser_error(lexer, NULL, NULL, NULL);
			return (NULL);
		}
	}
	result = pop_ast_stack(operand_stack);
	if (*operand_stack)
	{
		ft_error_msg("Syntax error: Invalid expression");
		handle_parser_error(lexer, NULL, NULL, &result);
		return (NULL);
	}
	return (result);
}

t_ast_node	*parse_command_with_redirects(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*cmd;

	skip_delims(lexer);
	if (lexer->tokens && lexer->tokens->type == TOKEN_LPAREN)
		return (parse_parenthesized_expression(lexer, operator_stack, operand_stack));
	cmd = parse_command(lexer);
	if (!cmd)
		return (NULL);
	while (lexer->tokens && is_redirection_token(lexer->tokens->type))
	{
		if (!add_redirection_to_command(lexer, cmd))
		{
			handle_parser_error(lexer, NULL, NULL, &cmd);
			return (NULL);
		}
		advance_token(lexer);
	}
	// printf("cmd_wredir- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	return (cmd);
}
