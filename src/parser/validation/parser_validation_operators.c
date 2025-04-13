/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_operators.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:04:56 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:37:53 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

bool	v_ops3(t_lexer *l)
{
	l->error = 1;
	print_syntax_error("newline");
	return (false);
}

bool	v_ops2(t_lexer *l, t_token *c)
{
	l->error = 1;
	print_syntax_error(c->value);
	return (false);
}

bool	validate_operators(t_lexer *lexer)
{
	t_token	*current;
	t_token	*prev;

	current = lexer->tokens;
	prev = NULL;
	while (current)
	{
		if (prev && is_operator_token(prev->type)
			&& is_operator_token(current->type))
		{
			if (!((prev->type == TOKEN_PIPE && current->type == TOKEN_PIPE)
					|| (prev->type == TOKEN_AMPERSAND
						&& current->type == TOKEN_AMPERSAND)))
				return (v_ops2(lexer, current));
		}
		if (!prev && is_operator_token(current->type)
			&& current->type != TOKEN_LPAREN)
			return (v_ops2(lexer, current));
		prev = current;
		current = current->next;
	}
	if (prev && is_operator_token(prev->type) && prev->type != TOKEN_RPAREN)
		return (v_ops3(lexer));
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
				print_syntax_error("|");
				return (false);
			}
			command_found = false;
		}
		else if (is_command_token(current->type)
			|| is_argument_token(current->type))
			command_found = true;
		current = current->next;
	}
	return (true);
}
