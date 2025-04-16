/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:04:44 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/07 22:04:46 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

bool	validate_input(t_lexer *lexer, const char *input)
{
	if (!validate_quotes(input)
	|| !validate_parens(lexer)
	|| !validate_ops(lexer)
	|| !validate_pipes(lexer)
	|| !validate_redirs(lexer))
	{
		lexer->error = 1;
		return (false);
	}
	return (true);
}

bool	validate_quotes(const char *input)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while(*input)
	{
		if (*input == SINGLE_QUOTE && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*input == DOUBLE_QUOTE && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		input++;
	}
	if (in_single_quotes)
	{
		ft_error_msg("minishell: syntax error: unclosed single quote");
		return (false);
	}
	if (in_double_quotes)
	{
		ft_error_msg("minishell: syntax error: unclosed double quote");
		return (false);
	}
	return (true);
}

bool	validate_parens(t_lexer *lexer)
{
	int		parentheses_count;
	t_token	*current;

	parentheses_count = 0;
	current = lexer->tokens;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			parentheses_count++;
		else if (current->type == TOKEN_RPAREN)
			parentheses_count--;
		if (parentheses_count < 0)
		{
			lexer->error = 1;
			ft_error_msg("minishell: syntax error: unexpected ')', unmatched parentheses");
			return (false);
		}
		current = current->next;
	}
	if (parentheses_count > 0)
	{
		lexer->error = 1;
		ft_error_msg("minishell: syntax error: unexpected EOF, unmatched parentheses");
		return (false);
	}
	return (true);
}