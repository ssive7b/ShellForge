#include "lexer.h"
#include "../../libft/include/libft.h"
#include <stdio.h>

void	ft_finalize_token(t_lexer *lx)
{
	if (lx->buff_idx > 0)
	{
		lx->buffer[lx->buff_idx] = '\0';
		ft_append_token(&lx->tokens, lx->buffer);
		lx->buff_idx = 0;
	}
}

void	ft_handle_default_state(t_lexer *lx, char current_char)
{
	if (ft_is_whitespace(current_char) || current_char == '\0')
		ft_finalize_token(lx);
	else if (current_char == '\'')
		lx->state = LEXER_IN_SING_QUOTE;
	else if (current_char == '"')
		lx->state = LEXER_IN_DOUBLE_QUOTE;
	else if (current_char == '#')
		lx->state = LEXER_IN_COMMENT;
	else
		lx->buffer[lx->buff_idx++] = current_char;
}

void	ft_handle_single_quote_state(t_lexer *lx, char current_char)
{
	if (current_char == '\'')
	{
		lx->state = LEXER_DEFAULT;
		lx->buffer[lx->buff_idx] = '\0';
		ft_append_token(lx, ft_create_token(TOKEN_QUOTE, lx->buffer));
		lx->buff_idx = 0;
	}
	else
		lx->buffer[lx->buff_idx++] = current_char;
}

void	ft_handle_double_quote_state(t_lexer *lx, char current_char)
{
	if (current_char == '"')
	{
		lx->state = LEXER_DEFAULT;
		lx->buffer[lx->buff_idx] = '\0';
		ft_append_token(lx, ft_create_token(TOKEN_QUOTE, lx->buffer));
		lx->buff_idx = 0;
	}
	else
		lx->buffer[lx->buff_idx++] = current_char;
}