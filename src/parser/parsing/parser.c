/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
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

t_anode	*parse_toks(t_lexer *lexer)
{
	t_stack	*operator_stack;
	t_stack *operand_stack;
	t_anode	*result_expr;

	operator_stack = NULL;
	operand_stack = NULL;
	result_expr = parse_expr(lexer, &operator_stack, &operand_stack);
	if (!result_expr || lexer->tokens || lexer->error)
	{
		ft_error_msg("Error: Failed while parsing tokens");
		parse_err(lexer, NULL, NULL, &result_expr);
		return (NULL);
	}
	stack_free(&operator_stack);
	stack_free(&operand_stack);
	return (result_expr);
}

t_anode	*parse_expr(t_lexer *lexer, t_stack **operator_stack, t_stack **operand_stack)
{
	t_anode	*first_operand;
	t_anode	*finalized_expression;

	first_operand = parse_cmd_redir(lexer, operator_stack, operand_stack);
	if (!first_operand)
		return (NULL);
	if (!stack_push(operand_stack, first_operand))
		return (NULL);
	// printf("parse_expr- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	if (!parse_infix(lexer, operator_stack, operand_stack))
		return (NULL);
	finalized_expression = finalize_expr(operator_stack, operand_stack, lexer);
	return (finalized_expression);
}

bool	parse_infix(t_lexer *lexer, t_stack **operator_stack, t_stack **operand_stack)
{
	t_anode	*next_operand;

	skip_delims(lexer);
	// printf("parse_infix- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	while (lexer->tokens && is_op_tok(lexer->tokens->type))
	{
		// printf("[inside loop] parse_infix- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
		if (!handle_op_prec(lexer, operator_stack, operand_stack))
			return (false);
		next_operand = parse_cmd_redir(lexer, operator_stack, operand_stack);
		if (!next_operand)
			return (false);
		if (!stack_push(operand_stack, next_operand))
			return (false);
	}
	return (true);
}

t_anode	*finalize_expr(t_stack **operator_stack, t_stack **operand_stack, t_lexer *lexer)
{
	t_anode	*result;

	while (*operator_stack)
	{
		if (!apply_op(operator_stack, operand_stack))
		{
			ft_error_msg("Error: Failed to process operator");
			parse_err(lexer, NULL, NULL, NULL);
			return (NULL);
		}
	}
	result = stack_pop(operand_stack);
	if (*operand_stack)
	{
		ft_error_msg("Syntax error: Invalid expression");
		parse_err(lexer, NULL, NULL, &result);
		return (NULL);
	}
	return (result);
}

t_anode	*parse_cmd_redir(t_lexer *lexer, t_stack **operator_stack, t_stack **operand_stack)
{
	t_anode	*cmd;

	skip_delims(lexer);
	if (lexer->tokens && lexer->tokens->type == TOKEN_LPAREN)
		return (parse_paren_expr(lexer, operator_stack, operand_stack));
	cmd = parse_cmd(lexer);
	if (!cmd)
		return (NULL);
	while (lexer->tokens && is_redir_tok(lexer->tokens->type))
	{
		if (!add_redir(lexer, cmd))
		{
			parse_err(lexer, NULL, NULL, &cmd);
			return (NULL);
		}
		next_token(lexer);
	}
	// printf("cmd_wredir- received: %d %s\n", lexer->tokens->type, lexer->tokens->value);
	return (cmd);
}
