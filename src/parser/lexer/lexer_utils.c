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

t_token	*ft_create_token(t_token token_data)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	*new_token = token_data;
	new_token->next = NULL;
	return (new_token);
}

void	ft_append_token(t_token **tokens_queue, t_token *new_token)
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

void	ft_print_tokens(t_token *tokens)
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
