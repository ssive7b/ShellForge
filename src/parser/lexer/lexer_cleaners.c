/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:10:57 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/05 00:10:58 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "utils.h"

static void	free_single_token(t_token *token);

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		free_single_token(current);
		current = next;
	}
}

void	cleanup_lexer(t_lexer **lexer)
{
	if (!lexer || !(*lexer))
		return ;
	safe_free((void **)&(*lexer)->input);
	free_tokens((*lexer)->head);
	(*lexer)->head = NULL;
	safe_free((void **)lexer);
}

static void	free_single_token(t_token *token)
{
	if (!token)
		return ;
	safe_free((void **)&token->value);
	safe_free((void **)&token);
}
