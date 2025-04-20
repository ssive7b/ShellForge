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

bool	handle_op_prec(t_lexer *lex, t_stack **ops, t_stack **opnds)
{
	t_ntype	current_op_type;
	t_anode	*op_node;
	int		current_op_prec;

	current_op_type = tok_to_node(lex->tokens->type);
	current_op_prec = op_precedence(current_op_type);
	while (*ops && op_precedence((*ops)->node->type) >= current_op_prec)
	{
		if (!apply_op(ops, opnds))
			return (false);
	}
	op_node = setup_empty_node(current_op_type, lex->tokens);
	if (!op_node)
		return (false);
	if (!stack_push(ops, op_node))
		return (false);
	next_token(lex);
	return (true);
}

t_anode	*parse_cmd(t_lexer *lex)
{
	t_anode	*node;

	if (!lex->tokens
		|| (!is_arg_tok(lex->tokens->type) && !is_redir_tok(lex->tokens->type)))
		return (parse_err(lex, NULL, NULL, NULL), NULL);
	node = setup_empty_node(NODE_COMMAND, lex->tokens);
	if (!node)
		return (parse_err(lex, NULL, NULL, NULL), NULL);
	if (is_redir_tok(lex->tokens->type))
		return (node);
	if (!setup_command_node(node, lex->tokens->value))
	{
		ft_error_msg("Error: Memory allocation failed in node_new()");
		node_free(&node);
		return (NULL);
	}
	if (!next_token(lex))
		return (parse_err(lex, NULL, NULL, NULL), NULL);
	if (!parse_command_arguments(lex, node))
	{
		parse_err(lex, NULL, NULL, &node);
		return (NULL);
	}
	return (node);
}

t_anode	*parse_paren_expr(t_lexer *lex, t_stack **ops, t_stack **opnds)
{
	t_anode	*expr;

	next_token(lex);
	expr = parse_expr(lex, ops, opnds);
	if (!expr)
	{
		parse_err(lex, NULL, NULL, NULL);
		return (NULL);
	}
	if (!lex->tokens || lex->tokens->type != TOKEN_RPAREN)
	{
		ft_error_msg("Error: Missing closing parenthesis");
		parse_err(lex, NULL, NULL, &expr);
		return (NULL);
	}
	next_token(lex);
	return (expr);
}

bool	parse_command_arguments(t_lexer *lex, t_anode *cmd)
{
	char	*arg;
	bool	success;

	skip_delims(lex);
	while (lex->tokens && is_arg_tok(lex->tokens->type))
	{
		arg = join_consecutive_tokens(lex);
		if (!arg)
			return (false);
		success = add_arg(cmd, arg);
		safe_free((void **)&arg);
		if (!success)
			return (false);
		while (lex->tokens && lex->tokens->type == TOKEN_DELIMITER)
			next_token(lex);
	}
	return (true);
}

char	*join_consecutive_tokens(t_lexer *lex)
{
	char	*arg;
	char	*temp;

	arg = ft_strdup(lex->tokens->value);
	if (!arg)
		return (NULL);
	next_token(lex);
	while (lex->tokens && is_arg_tok(lex->tokens->type))
	{
		temp = arg;
		arg = ft_strjoin(temp, lex->tokens->value);
		safe_free((void **)&temp);
		if (!arg)
			return (NULL);
		next_token(lex);
	}
	return (arg);
}
