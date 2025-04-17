/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_operators.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:04:56 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/07 22:04:57 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

static bool	op_err(t_lexer *lexer, char *value);

bool	validate_ops(t_lexer *lexer)
{
	t_token	*current;
	t_token	*prev;

	current = lexer->tokens;
	prev = NULL;
	while (current)
	{
		if (prev && is_op_tok(prev->type) && is_op_tok(current->type))
			return (op_err(lexer, current->value));
		if (!prev && is_op_tok(current->type) && current->type != TOKEN_LPAREN)
			return (op_err(lexer, current->value));
		prev = current;
		current = current->next;
	}
	if (prev && is_op_tok(prev->type) && prev->type != TOKEN_RPAREN)
		return (op_err(lexer, "newline"));
	return (true);
}

bool	validate_pipes(t_lexer *lexer)
{
	t_token	*current;
	bool	command_found;

	current = lexer->tokens;
	command_found = false;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!command_found)
			{
				lexer->error = 1;
				print_syn_err("|");
				return (false);
			}
			command_found = false;
		}
		else if (is_cmd_tok(current->type) || is_arg_tok(current->type))
			command_found = true;
		current = current->next;
	}
	return (true);
}

static bool	op_err(t_lexer *lexer, char *value)
{
	lexer->error = 1;
	print_syn_err(value);
	return (false);
}
