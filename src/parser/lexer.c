#include "lexer.h"
#include "../../libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void ft_process_char(t_lexer *lx, char current_char);
static char	*get_prev_char(t_lexer *lx);

t_token	*ft_lexer(char *input)
{
	t_lexer	lexer;
	lexer.input = input;
	lexer.char_idx = 0;
	lexer.state = LEXER_DEFAULT;
	lexer.tokens = NULL;
	lexer.buff_idx = 0;
	lexer.token_buffer = ft_calloc(sizeof(input), 1);
	if (!lexer.token_buffer)
		return (NULL);
	while(lexer.input[lexer.char_idx])
	{
		ft_process_char(&lexer, lexer.input[lexer.char_idx]);
		lexer.char_idx++;
	}
	return (lexer.tokens);
}

static void ft_process_char(t_lexer *lx, char current_char)
{
	if (current_char == '\0')
		ft_finalize_token(lx);
	else if (ft_is_operator(get_prev_char(lx)) && lx->state != LEXER_IN_QUOTE && ft_is_double_operator(lx->token_buffer, lx->buff_idx))
		ft_append_token(TOKEN_OPERATOR); // [Placeholder] work on logic
	else if (ft_is_operator(get_prev_char(lx)) && !ft_is_double_operator(lx->token_buffer, lx->buff_idx))
		ft_finalize_token(lx);
	else if ((current_char == '\\' || ft_is_quote(current_char)) && lx->state != LEXER_IN_QUOTE)
		// [Placeholder] implement logic for what follows next
	else if (ft_is_expansion(current_char))
		// [Placeholder] handle Parameter/ Arithmetic Expansion + Command Substitution
	else if (!ft_is_quote(current_char) && ft_is_operator(current_char))
		ft_finalize_token(lx);
	else if (!ft_is_quote(current_char) && current_char == '\n')
		ft_finalize_token(lx);
	else if (!ft_is_quote(current_char) && ft_is_whitespace(current_char))
		ft_finalize_token(lx); // + discard current character
	else if (lx->buff_idx && lx->tokens->type) // prev char part of word
		return ;
	else if (current_char == '#')
		// discard all until new line (i.e. handle commented section)
	else // start of new word (check if buff->idx == 0?)
		lx->state = LEXER_IN_WORD
	


	if (lx->state == LEXER_DEFAULT)
		ft_handle_default_state(lx, current_char);
	else if (lx->state == LEXER_IN_SING_QUOTE)
		ft_handle_single_quote_state(lx, current_char);
	else if (lx->state == LEXER_IN_DOUBLE_QUOTE)
		ft_handle_double_quote_state(lx, current_char);
	else if (lx->state == LEXER_IN_COMMENT)
		return ;
}

static char	*get_prev_char(t_lexer *lx)
{
	size_t	current_buff_idx;

	current_buff_idx = lx->buff_idx;
	if (!lx->buff_idx)
		return (NULL);
	return (&lx->token_buffer[current_buff_idx - 1]);
}