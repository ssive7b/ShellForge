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

#include "minishell.h"
#include "lexer.h"
#include "char_designation.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static t_token_type		get_op_token_type(const char *input);
static t_lexer_state	word_state(t_lexer *lx);
static t_lexer_state	operator_state(t_lexer *lx);
static t_lexer_state	delimiter_state(t_lexer *lx);

t_token	*ft_lexer(char *input)
{
	t_lexer			lx;
	t_lexer_state	next_state;

	next_state = (t_lexer_state) word_state;
	ft_init_lex(&lx, input);
	lx.idx = ft_skip_whitespaces(input);
	while (next_state && input[lx.idx])
	{
		next_state = (t_lexer_state) next_state(&lx);
		lx.idx++;
	}
	return (lx.tokens);
}

static t_lexer_state	word_state(t_lexer *lx)
{
	t_token	token;
	size_t	start_idx;

	start_idx = lx->idx;
	if (lx->input[lx->idx] == DOUBLE_QUOTE)
	{
		token.type = TOKEN_WORD_DQUOTED;
		lx->idx += ft_find_char_idx(&lx->input[lx->idx + 1], DOUBLE_QUOTE) + 1;
	}
	else if (lx->input[lx->idx] == SINGLE_QUOTE)
	{
		token.type = TOKEN_WORD_SQUOTED;
		lx->idx += ft_find_char_idx(&lx->input[lx->idx + 1], SINGLE_QUOTE) + 1; 
	}
	else
	{
		token.type = TOKEN_WORD_UNQUOTED;
		while (ft_is_unquoted_char(lx->input[lx->idx]) || ft_is_escaped(lx->input, lx->idx))
			lx->idx++;
		lx->idx--;
	}
	token.value = ft_substr(lx->input, start_idx, lx->idx - start_idx + 1);
	if (ft_strlen(token.value) > 0)
		ft_append_token(&lx->tokens, ft_create_token(token));
	return ((t_lexer_state) delimiter_state);
}

t_lexer_state	operator_state(t_lexer *lx)
{
	size_t	len;
	t_token	token;

	token.type = get_op_token_type(&lx->input[lx->idx]);
	if (token.type == TOKEN_PIPE
		|| token.type == TOKEN_REDIR_OUT
		|| token.type == TOKEN_REDIR_IN)
		len = 1;
	else if (token.type == TOKEN_REDIR_APPEND
		|| token.type == TOKEN_REDIR_HEREDOC)
		len = 2;
	else
		return (NULL);
	token.value = ft_substr(lx->input, lx->idx, len); // rethink if we need it? can just put it as NULL and deduce from the type
	lx->idx = lx->idx + len - 1;
	if (ft_strlen(token.value) > 0)
		ft_append_token(&lx->tokens, ft_create_token(token));
	return ((t_lexer_state) delimiter_state);
}

static t_lexer_state	delimiter_state(t_lexer *lx)
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
		return ((t_lexer_state) operator_state);
	return ((t_lexer_state) word_state);
}

static t_token_type		get_op_token_type(const char *input)
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
	if (input[0] == '|')
		return (TOKEN_PIPE);
	return (TOKEN_UNKNOWN);
}
