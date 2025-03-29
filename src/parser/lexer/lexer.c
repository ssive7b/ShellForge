/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:57:52 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/14 00:57:55 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "char_designation.h"
#include "utils.h"
#include "parser.h"
#include "utils.h"

// Not sure what to do with a single & ??
// Return NULL or return it as a word or as an operator?

static t_token_type		get_op_token_type(const char *input);
static t_lexer_state	word_state(t_lexer *lx);
static t_lexer_state	operator_state(t_lexer *lx);
static t_lexer_state	handle_redirection(t_lexer *lx);
static t_lexer_state	delimiter_state(t_lexer *lx);

t_token	*ft_lexer(char *input)
{
	t_lexer			lx;
	t_lexer_state	next_state;

	next_state = (t_lexer_state)word_state;
	ft_init_lex(&lx, input);
	lx.idx = ft_skip_whitespaces(input);
	while (next_state && input[lx.idx])
	{
		next_state = (t_lexer_state)next_state(&lx);
		lx.idx++;
	}
	return (lx.tokens);
}

static t_lexer_state	word_state(t_lexer *lx)
{
	t_token	token;
	size_t	start_idx;
	char	*quoted_str;

	start_idx = lx->idx;
	if (lx->input[lx->idx] == DOUBLE_QUOTE)
	{
		token.type = TOKEN_WORD_DQUOTED;
		quoted_str = handle_quotes(lx, DOUBLE_QUOTE);
	}
	else if (lx->input[lx->idx] == SINGLE_QUOTE)
	{
		token.type = TOKEN_WORD_SQUOTED;
		quoted_str = handle_quotes(lx, SINGLE_QUOTE);
	}
	else
	{
		token.type = TOKEN_WORD_UNQUOTED;
		while (ft_is_unquoted_char(lx->input[lx->idx])
			|| ft_is_escaped(lx->input, lx->idx))
			lx->idx++;
		lx->idx--;
		quoted_str = ft_substr(lx->input, start_idx, lx->idx - start_idx + 1);
	}
	token.value = quoted_str;
	if (token.value && ft_strlen(token.value) > 0)
		ft_append_token(&lx->tokens, ft_create_token(token));
	if (lx->input[lx->idx + 1] == '\0')
		return (NULL);
	// Check if the next character is an operator or meta-character
	if (ft_is_operator(lx->input[lx->idx + 1]))
		return ((t_lexer_state)operator_state);
	return ((t_lexer_state)delimiter_state);
}

t_lexer_state	operator_state(t_lexer *lx)
{
	size_t	len;
	t_token	token;

	// Check if the current character is an operator
	if (!ft_is_operator(lx->input[lx->idx]))
		return (NULL);
	// Check if the next character forms a multi-character operator
	if (ft_check_form_op(lx->input[lx->idx], lx->input[lx->idx + 1]))
		len = 2;
	else
		len = 1;
	// Get the operator type
	token.type = get_op_token_type(&lx->input[lx->idx]);
	// If the operator type is invalid, skip it
	if (token.type == TOKEN_UNKNOWN)
		return (NULL);
	token.value = ft_substr(lx->input, lx->idx, len);
	// rethink if we need it? can just put it as NULL and deduce from the type
	if (!token.value || ft_strlen(token.value) == 0) // Prevent NULL values
		token.value = strdup("UNKNOWN_OP");
	// Use a placeholder instead of NULL
	// Append the token to the token list
	ft_append_token(&lx->tokens, ft_create_token(token));
	// Move index past the operator
	lx->idx += len;
	return ((t_lexer_state)word_state);
}

static t_lexer_state	handle_redirection(t_lexer *lx)
{
	t_token	token;
	char	cur_char;

	cur_char = lx->input[lx->idx];
	if (cur_char == '<')
	{
		token.value = "<";
		token.type = TOKEN_REDIR_IN;
	}
	else
	{
		token.value = ">";
		token.type = TOKEN_REDIR_OUT;
	}
	ft_append_token(&lx->tokens, ft_create_token(token));
	lx->idx++; // Move past '<' or '>'
	// Check for "<<" or ">>"
	if (lx->input[lx->idx] == cur_char)
	{
		if (cur_char == '<')
		{
			token.value = "<<";
			token.type = TOKEN_REDIR_HEREDOC;
		}
		else
		{
			token.value = ">>";
			token.type = TOKEN_REDIR_APPEND;
		}
		ft_append_token(&lx->tokens, ft_create_token(token));
		lx->idx++; // Move past the second '<' or '>'
	}
	return ((t_lexer_state)delimiter_state);
}

static t_lexer_state	delimiter_state(t_lexer *lx)
{
	t_token	token;
	size_t	count_skipped_spaces;

	// Skip whitespaces and get the next meaningful char
	count_skipped_spaces = ft_skip_whitespaces(&lx->input[lx->idx]);
	lx->idx += count_skipped_spaces - 1;
	// If we reached the end, append a TOKEN_END
	if (lx->idx == '\0')
	{
		token.value = NULL;
		token.type = TOKEN_END;
		ft_append_token(&lx->tokens, ft_create_token(token));
		return (NULL);
	}
	// Handle '<' and '>' as individual tokens
	if (lx->idx == '<' || lx->idx == '>')
		return (handle_redirection(lx));
	// If it's an operator, transition to operator state
	if (ft_is_meta_char(lx->idx))
		return ((t_lexer_state)operator_state);
	// Otherwise, transition to word state
	return ((t_lexer_state)word_state);
}

static t_token_type	get_op_token_type(const char *input)
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
		return (TOKEN_UNKNOWN);
	}
	if (input[0] == '|')
	{
		if (input[1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	return (TOKEN_UNKNOWN);
}
