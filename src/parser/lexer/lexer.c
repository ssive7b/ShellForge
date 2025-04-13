/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:57:52 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 21:56:56 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_lexer	*run_tokenizer(const char *input)
{
	t_lexer			*lx;
	t_lexer_state	next_state;

	next_state = (t_lexer_state)word_state;
	lx = init_tokenizer(input);
	if (!lx)
		return (NULL);
	lx->idx = ft_skip_whitespaces(input);
	while (next_state && input[lx->idx])
	{
		next_state = (t_lexer_state)next_state(lx);
		lx->idx++;
	}
	return (lx);
}

t_lexer_state	delimiter_state(t_lexer *lx)
{
	t_token	token;
	size_t	count_skipped_spaces;
	char	next_non_whitespace_char;

	count_skipped_spaces = ft_skip_whitespaces(&lx->input[lx->idx]);
	next_non_whitespace_char = lx->input[lx->idx + count_skipped_spaces];
	if (next_non_whitespace_char == '\0')
		return (NULL);
	if (count_skipped_spaces)
	{
		lx->idx += count_skipped_spaces - 1;
		token.value = NULL;
		token.type = TOKEN_DELIMITER;
		ft_append_token(&lx->tokens, ft_create_token(token));
	}
	else
		lx->idx += -1;
	if (ft_is_meta_char(next_non_whitespace_char))
		return ((t_lexer_state)operator_state);
	return ((t_lexer_state)word_state);
}

t_token_type	get_op_token_type2(const char *input)
{
	if (input[0] == '|')
	{
		if (input[1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	if (input[0] == ';')
		return (TOKEN_SEMICOLON);
	if (input[0] == '(')
		return (TOKEN_LPAREN);
	if (input[0] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_UNKNOWN);
}

t_token_type	get_op_token_type(const char *input)
{
	if (!input || !*input)
		return (TOKEN_UNKNOWN);
	if (input[0] == '>')
	{
		if (input[1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	if (input[0] == '<')
	{
		if (input[1] == '<')
			return (TOKEN_REDIR_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (input[0] == '&')
	{
		if (input[1] == '&')
			return (TOKEN_AND);
		return (TOKEN_AMPERSAND);
	}
	return (get_op_token_type2(input));
}
