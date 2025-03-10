#include "lexer.h"
#include "../../libft/include/libft.h"
#include <stdio.h>

t_token	*ft_create_token(t_token_type type, const char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	ft_append_token(t_lexer *lexer, t_token *new_token)
{
	t_token	*temp;

	if(!lexer->tokens)
	{
		lexer->tokens = new_token;
		new_token->prev = NULL;
		new_token->next = NULL;
	}
	else
	{
		temp = lexer->tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->next = NULL;
		new_token->prev = temp;
	}
}

void	ft_finalize_token(t_lexer *lx, t_token_type type)
{
	if (lx->buff_idx > 0)
	{
		lx->token_buffer[lx->buff_idx] = '\0';
		ft_append_token(lx, ft_create_token(type, lx->token_buffer));
		lx->buff_idx = 0;
	}
}

void	ft_append_char(t_lexer *lx, char c)
{
	lx->token_buffer[lx->buff_idx] = c;
	lx->buff_idx++;
}