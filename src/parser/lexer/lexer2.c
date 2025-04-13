/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:35:19 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 22:02:37 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char_designation.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	handle_single_quote(t_token token, t_lexer *lx)
{
	token.type = TOKEN_WORD_SQUOTED;
	lx->idx += ft_char_qadjusted(&lx->input[lx->idx + 1], SINGLE_QUOTE) + 1;
}

t_lexer_state	word_state(t_lexer *lx)
{
	t_token	token;
	size_t	start_idx;

	start_idx = lx->idx;
	if (lx->input[lx->idx] == DOUBLE_QUOTE)
	{
		token.type = TOKEN_WORD_DQUOTED;
		lx->idx += ft_char_qadjusted(&lx->input[lx->idx + 1], DOUBLE_QUOTE) + 1;
	}
	else if (lx->input[lx->idx] == SINGLE_QUOTE)
		handle_single_quote(token, lx);
	else
	{
		token.type = TOKEN_WORD_UNQUOTED;
		while (ft_is_unquoted_char(lx->input[lx->idx])
			|| ft_is_escaped(lx->input, lx->idx))
			lx->idx++;
		lx->idx--;
	}
	token.value = ft_substr(lx->input, start_idx, lx->idx - start_idx + 1);
	if (!token.value)
		return (NULL);
	if (ft_strlen(token.value) > 0)
		ft_append_token(&lx->tokens, ft_create_token(token));
	return ((t_lexer_state)delimiter_state);
}

t_lexer_state	operator_state(t_lexer *lx)
{
	size_t	len;
	t_token	token;

	token.type = get_op_token_type(&lx->input[lx->idx]);
	if (token.type == TOKEN_PIPE || token.type == TOKEN_REDIR_OUT
		|| token.type == TOKEN_REDIR_IN || token.type == TOKEN_AMPERSAND
		|| token.type == TOKEN_SEMICOLON || token.type == TOKEN_LPAREN
		|| token.type == TOKEN_RPAREN)
		len = 1;
	else if (token.type == TOKEN_REDIR_APPEND
		|| token.type == TOKEN_REDIR_HEREDOC || token.type == TOKEN_AND
		|| token.type == TOKEN_OR)
		len = 2;
	else
		return (NULL);
	token.value = ft_substr(lx->input, lx->idx, len);
	if (!token.value)
		return (NULL);
	lx->idx = lx->idx + len - 1;
	if (ft_strlen(token.value) > 0)
		ft_append_token(&lx->tokens, ft_create_token(token));
	return ((t_lexer_state)delimiter_state);
}
