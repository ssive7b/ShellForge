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

static t_token_type		get_op_token_type(const char *input);
static t_lexer_state	word_state(t_lexer *lx);
static t_lexer_state	operator_state(t_lexer *lx);
static t_lexer_state	delimiter_state(t_lexer *lx);

t_lexer	*run_tokenizer(const char *input)
{
	t_lexer			*lx;
	t_lexer_state	next_state;

	next_state = (t_lexer_state) word_state;
	lx = init_tokenizer(input);
	if (!lx)
		return (lx->error = 1, NULL);
	lx->idx = skip_whitesps(input);
	while (next_state && input[lx->idx])
	{
		next_state = (t_lexer_state) next_state(lx);
		if (!next_state)
		{
			lx->error = 1;
			cleanup_lexer(&lx);
			return (NULL);
		}
		lx->idx++;
	}
	return (lx);
}

static t_lexer_state	word_state(t_lexer *lx)
{
	t_token	token;
	size_t	start;

	start = lx->idx;
	extract_word_token(lx, &token, start);
	if (!token.value)
		return (NULL);
	if (ft_strlen(token.value) > 0)
		if (!append_token(&lx->tokens, clone_token(token)))
			return (safe_free((void **)&token.value), NULL);
	safe_free((void **)&token.value);
	return ((t_lexer_state) delimiter_state);
}

t_lexer_state	operator_state(t_lexer *lx)
{
	size_t	len;
	t_token	token;

	token.type = get_op_token_type(&lx->input[lx->idx]);
	if (token.type == TOKEN_PIPE
		|| token.type == TOKEN_REDIR_OUT || token.type == TOKEN_REDIR_IN
		|| token.type == TOKEN_AMPERSAND || token.type == TOKEN_SEMICOLON
		|| token.type == TOKEN_LPAREN || token.type == TOKEN_RPAREN)
		len = 1;
	else if (token.type == TOKEN_REDIR_APPEND
		|| token.type == TOKEN_REDIR_HEREDOC
		|| token.type == TOKEN_AND || token.type == TOKEN_OR)
		len = 2;
	else
		return (NULL);
	token.value = ft_substr(lx->input, lx->idx, len);
	if (!token.value)
		return (NULL);
	lx->idx = lx->idx + len - 1;
	if (ft_strlen(token.value) > 0)
		if (!append_token(&lx->tokens, clone_token(token)))
			return (safe_free((void **)&token.value), NULL);
	safe_free((void **)&token.value);
	return ((t_lexer_state) delimiter_state);
}

static t_lexer_state	delimiter_state(t_lexer *lx)
{
	t_token	token;
	size_t	count_skipped_spaces;
	char	next_non_whitespace_char;

	count_skipped_spaces = skip_whitesps(&lx->input[lx->idx]);
	next_non_whitespace_char = lx->input[lx->idx + count_skipped_spaces];
	if (next_non_whitespace_char == '\0')
		return (NULL);
	if (count_skipped_spaces)
	{
		lx->idx += count_skipped_spaces - 1;
		token.value = NULL;
		token.type = TOKEN_DELIMITER;
		append_token(&lx->tokens, clone_token(token));
	}
	else
		lx->idx += -1;
	if (is_meta_char(next_non_whitespace_char))
		return ((t_lexer_state) operator_state);
	return ((t_lexer_state) word_state);
}

static t_token_type	get_op_token_type(const char *input)
{
	if (!input || !*input)
		return (TOKEN_UNKNOWN);
	if (input[0] == '>' && input[1] == '>')
		return (TOKEN_REDIR_APPEND);
	if (input[0] == '>')
		return (TOKEN_REDIR_OUT);
	if (input[0] == '<' && input[1] == '<')
		return (TOKEN_REDIR_HEREDOC);
	if (input[0] == '<')
		return (TOKEN_REDIR_IN);
	if (input[0] == '&' && input[1] == '&')
		return (TOKEN_AND);
	if (input[0] == '&')
		return (TOKEN_AMPERSAND);
	if (input[0] == '|' && input[1] == '|')
		return (TOKEN_OR);
	if (input[0] == '|')
		return (TOKEN_PIPE);
	if (input[0] == ';')
		return (TOKEN_SEMICOLON);
	if (input[0] == '(')
		return (TOKEN_LPAREN);
	if (input[0] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_UNKNOWN);
}
