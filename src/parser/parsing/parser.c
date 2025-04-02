/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:25:50 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 00:25:51 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

t_ast_node	*parse_tokens(t_lexer *lexer)
{
	t_ast_node	*result;

	result = parse_expression(lexer);
	if ((result && lexer->tokens) || lexer->error)
	{
		perror("Error: Unexpected token after expression\n");
		handle_parser_error(lexer, NULL, NULL, &result);
		return (NULL);
	}
	return (result);
}

t_ast_node	*parse_expression(t_lexer *lexer)
{
	t_ast_stack	*operator_stack;
	t_ast_stack	*operand_stack;
	t_ast_node	*first_operand;
	t_ast_node	*finalized_expression;

	operator_stack = NULL;
	operand_stack = NULL;
	first_operand = parse_command_with_redirects(lexer);
	if (!first_operand)
		return (NULL);
	if (!push_ast_stack(&operand_stack, first_operand))
	{
		handle_parser_error(lexer, NULL, NULL, &first_operand);
		return (NULL);
	}
	if (!parse_infix_operators(lexer, &operator_stack, &operand_stack))
	{
		handle_parser_error(lexer, NULL, NULL, NULL);
		return (NULL);
	}
	finalized_expression = finalize_expression(&operator_stack, &operand_stack, lexer);
	return (finalized_expression);
}

bool	parse_infix_operators(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*next_operand;

	while (lexer->tokens && is_operator_token(lexer->tokens->type))
	{
		if (!handle_operator_precedence(lexer, operator_stack, operand_stack))
			return (false);
		next_operand = parse_command_with_redirects(lexer);
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
			perror("Error: Failed to process operator");
			handle_parser_error(lexer, operator_stack, NULL, NULL);
			return (NULL);
		}
	}
	result = pop_ast_stack(operand_stack);
	if (*operand_stack)
	{
		perror("Syntax error: invalid expression");
		handle_parser_error(lexer, NULL, operand_stack, NULL);
		return (NULL);
	}
	return (result);
}

t_ast_node	*parse_command_with_redirects(t_lexer *lexer)
{
	t_ast_node	*cmd;

	if (lexer->tokens && lexer->tokens->type == TOKEN_LPAREN)
		return (parse_parenthesized_expression(lexer));
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
	}
	return (cmd);
}
