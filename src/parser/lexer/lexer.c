#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void ft_process_char(t_lexer *lx, char current_char);

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
	ft_finalize_token(&lexer, TOKEN_EOF);
	return (lexer.tokens);
}

static void ft_process_char(t_lexer *lx, char current_char)
{
	if (current_char == '\0')
		return (ft_handle_eof(lx));
	else if (ft_is_operator(current_char) && lx->state != LEXER_IN_SINGLE_QUOTE && lx->state != LEXER_IN_DOUBLE_QUOTE) // fix logic
		return (ft_handle_operator(lx, current_char));
	else if (ft_is_quote(current_char) && lx->state != LEXER_IN_OPERATOR) // fix logic
		return (ft_handle_quotes(lx, current_char));
	else if (ft_is_expansion(current_char) && lx->state != LEXER_IN_SINGLE_QUOTE)
		return (ft_handle_expansion(lx, current_char));
	else if (ft_is_operator(current_char) && lx->state == LEXER_DEFAULT)
		return (ft_handle_standalone_operator(lx, current_char));
	else if (current_char == '\n')
		return (ft_handle_newline(lx));
	else if (ft_is_whitespace(current_char) && lx->state == LEXER_DEFAULT)
		return (ft_handle_whitespace(lx));
	else if (lx->buff_idx)
		return (ft_handle_word_continuation(lx, current_char));
	else if (current_char == '#' && lx->state == LEXER_DEFAULT)
		return (ft_handle_comment(lx));
	else
		return (ft_handle_new_word(lx, current_char));
}
