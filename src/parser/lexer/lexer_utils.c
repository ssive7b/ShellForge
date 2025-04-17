/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:58:06 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/14 00:58:07 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "utils.h"
#include "char_designation.h"

t_lexer	*init_tokenizer(const char *input)
{
	t_lexer	*lx;

	if (!input)
		return (NULL);
	lx = malloc(sizeof(t_lexer));
	if (!lx)
		return (NULL);
	lx->input = ft_strdup(input);
	if (!lx->input)
		return (NULL);
	lx->idx = 0;
	lx->tokens = NULL;
	lx->error = 0;
	return (lx);
}

t_token	*create_token(t_token token_data)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	*new_token = token_data;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **tokens_queue, t_token *new_token)
{
	t_token	*last_token;

	if (!*tokens_queue)
	{
		*tokens_queue = new_token;
		return ;
	}
	last_token = *tokens_queue;
	while (last_token->next)
		last_token = last_token->next;
	last_token->next = new_token;
}

void	print_tokens(t_token *tokens)
{
	t_token	*current_token;
	char	*token_value;
	int		token_type;

	current_token = tokens;
	while (current_token)
	{
		token_value = current_token->value;
		token_type = current_token->type;
		printf("Token: value: <%s>\ttype: <%d>\n", token_value, token_type);
		current_token = current_token->next;
	}
}

size_t	extract_word_token(t_lexer *lx, t_token *token, size_t start)
{
	if (lx->input[lx->idx] == DOUBLE_QUOTE)
	{
		token->type = TOKEN_WORD_DQUOTED;
		lx->idx += find_char_qadj(&lx->input[lx->idx + 1], DOUBLE_QUOTE) + 1;
		token->value = ft_substr(lx->input, start + 1, lx->idx - start - 1);
	}
	else if (lx->input[lx->idx] == SINGLE_QUOTE)
	{
		token->type = TOKEN_WORD_SQUOTED;
		lx->idx += find_char_qadj(&lx->input[lx->idx + 1], SINGLE_QUOTE) + 1;
		token->value = ft_substr(lx->input, start + 1, lx->idx - start - 1);
	}
	else
	{
		token->type = TOKEN_WORD_UNQUOTED;
		while (is_unq_char(lx->input[lx->idx]) || is_esc(lx->input, lx->idx))
			lx->idx++;
		lx->idx--;
		token->value = ft_substr(lx->input, start, lx->idx - start + 1);
	}
	return (lx->idx);
}
