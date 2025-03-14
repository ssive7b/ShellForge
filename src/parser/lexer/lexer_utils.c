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

#include "lexer.h"

void	ft_init_lex(t_lexer *lx, char *input)
{
	lx->input = input;
	lx->idx = 0;
	lx->line_number = 1;
	lx->column_number = 1;
	lx->tokens = NULL;
	lx->error = 0;
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
	while(current_token->next)
	{
		token_value = current_token->value;
		token_type = current_token->type;
		printf("Token: value: <%s>\ttype: <%d>\n", token_value, token_type);
		current_token = current_token->next;
	}
}
