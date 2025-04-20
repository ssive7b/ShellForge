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

t_anode	*parse_toks(t_lexer *lex)
{
	t_stack	*ops;
	t_stack	*opnds;
	t_anode	*result_expr;

	if (!lex->tokens)
		return (NULL);
	ops = NULL;
	opnds = NULL;
	result_expr = parse_expr(lex, &ops, &opnds);
	if (!result_expr || lex->tokens || lex->error)
	{
		print_tokens(lex->tokens);
		ft_error_msg("Error: Failed while parsing tokens");
		parse_err(lex, NULL, NULL, &result_expr);
		return (NULL);
	}
	stack_free(&ops);
	stack_free(&opnds);
	return (result_expr);
}

t_anode	*parse_expr(t_lexer *lex, t_stack **ops, t_stack **opnds)
{
	t_anode	*first_operand;
	t_anode	*finalized_expression;

	first_operand = parse_cmd_redir(lex, ops, opnds);
	if (!first_operand)
		return (NULL);
	if (!stack_push(opnds, first_operand))
		return (NULL);
	if (!parse_infix(lex, ops, opnds))
		return (NULL);
	finalized_expression = finalize_expr(ops, opnds, lex);
	return (finalized_expression);
}

bool	parse_infix(t_lexer *lex, t_stack **ops, t_stack **opnds)
{
	t_anode	*next_operand;

	skip_delims(lex);
	while (lex->tokens && is_op_tok(lex->tokens->type))
	{
		if (!handle_op_prec(lex, ops, opnds))
			return (false);
		next_operand = parse_cmd_redir(lex, ops, opnds);
		if (!next_operand)
			return (false);
		if (!stack_push(opnds, next_operand))
			return (false);
	}
	return (true);
}

t_anode	*finalize_expr(t_stack **ops, t_stack **opnds, t_lexer *lex)
{
	t_anode	*result;

	while (*ops)
	{
		if (!apply_op(ops, opnds))
		{
			ft_error_msg("Error: Failed to process operator");
			parse_err(lex, NULL, NULL, NULL);
			return (NULL);
		}
	}
	result = stack_pop(opnds);
	if (*opnds)
	{
		ft_error_msg("Syntax error: Invalid expression");
		parse_err(lex, NULL, NULL, &result);
		return (NULL);
	}
	return (result);
}

t_anode	*parse_cmd_redir(t_lexer *lex, t_stack **ops, t_stack **opnds)
{
	t_anode	*cmd;

	skip_delims(lex);
	if (lex->tokens && lex->tokens->type == TOKEN_LPAREN)
		return (parse_paren_expr(lex, ops, opnds));
	cmd = parse_cmd(lex);
	if (!cmd)
		return (NULL);
	while (lex->tokens
		&& (is_arg_tok(lex->tokens->type) || is_redir_tok(lex->tokens->type)))
	{
		if (is_redir_tok(lex->tokens->type))
		{
			if (!add_redir(lex, cmd))
				return (parse_err(lex, NULL, NULL, &cmd), NULL);
			skip_delims(lex);
		}
		else if (is_arg_tok(lex->tokens->type))
		{
			if (!parse_command_arguments(lex, cmd))
				return (parse_err(lex, NULL, NULL, &cmd), NULL);
		}
	}
	return (cmd);
}
