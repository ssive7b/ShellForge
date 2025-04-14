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

bool	validate_operators(t_lexer *lexer) // Ensures that consecutive operators are handled correctly
{
	t_token	*current;
	t_token	*prev;

	current = lexer->tokens;
	prev = NULL;
	while(current)
	{
		if (prev && is_operator_token(prev->type) && is_operator_token(current->type))
		{
			lexer->error = 1;
			print_syntax_error(current->value);
			return (false);
		}
		if (!prev && is_operator_token(current->type) && current->type != TOKEN_LPAREN)
		{
			lexer->error = 1;
			print_syntax_error(current->value);
			return (false);
		}
		prev = current;
		current = current->next;
	}
	if (prev && is_operator_token(prev->type) && prev->type != TOKEN_RPAREN)
	{
		lexer->error = 1;
		print_syntax_error("newline");
		return (false);
	}
	return (true);
}

bool validate_pipes(t_lexer *lexer) // check for consecutive piping operators or if input starts with a pipe
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
		else if (is_command_token(current->type) || is_argument_token(current->type))
			command_found = true;
		current = current->next;
	}
	return (true);
}