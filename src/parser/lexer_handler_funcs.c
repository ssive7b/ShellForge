#include "lexer.h"
#include "../../libft/include/libft.h"
#include <stdio.h>

void	ft_handle_eof(t_lexer *lx)
{
	ft_finalize_token(lx, TOKEN_EOF);
}

void	ft_handle_operator(t_lexer *lx, char c)
{
	if (lx->state == LEXER_IN_OPERATOR && ft_is_operator(lx->token_buffer[lx->buff_idx - 1]))
		ft_append_char(lx, c);
	else
	{
		ft_finalize_token(lx, TOKEN_OPERATOR);
		ft_append_char(lx, c);
		lx->state = LEXER_IN_OPERATOR;
	}
}

void	ft_handle_quotes(t_lexer *lx, char c)
{
	if (c == '\'' && lx->state != LEXER_IN_DOUBLE_QUOTE)
	{
		if (lx->state == LEXER_IN_SINGLE_QUOTE)
			lx->state = LEXER_DEFAULT;
		else
			lx->state = LEXER_IN_SINGLE_QUOTE;
	}
	else if (c == '"' && lx->state != LEXER_IN_SINGLE_QUOTE)
	{
		if (lx->state == LEXER_IN_DOUBLE_QUOTE)
			lx->state = LEXER_DEFAULT;
		else
			lx->state = LEXER_IN_DOUBLE_QUOTE;
	}
	ft_append_char(lx, c);
	ft_finalize_token(lx, TOKEN_QUOTE);
}

void	ft_handle_expansion(t_lexer *lx, char c)
{
	lx->state = LEXER_IN_EXPANSION;
	ft_append_char(lx, c);
	ft_finalize_token(lx, TOKEN_EXPANSION);
}

void	ft_handle_standalone_operator(t_lexer *lx, char c)
{
	ft_finalize_token(lx, TOKEN_OPERATOR);
	ft_append_char(lx, c);
	lx->state = LEXER_IN_OPERATOR;
}

void	ft_handle_newline(t_lexer *lx)
{
	ft_finalize_token(lx, TOKEN_NEWLINE);
}

void	ft_handle_whitespace(t_lexer *lx)
{
	ft_finalize_token(lx, TOKEN_WHITESPACE);
}

void	ft_handle_word_continuation(t_lexer *lx, char c)
{
	ft_append_char(lx, c);
}

void	ft_handle_comment(t_lexer *lx)
{
	lx->state = LEXER_IN_COMMENT;
	while (lx->input[lx->char_idx] != '\n' && lx->input[lx->char_idx] != '\0')
		lx->char_idx++;
}

void	ft_handle_new_word(t_lexer *lx, char c)
{
	ft_finalize_token(lx, TOKEN_WORD);
	ft_append_char(lx, c);
}