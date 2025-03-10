#include "lexer.h"
#include "../../libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void ft_process_char(t_lexer *lx, char current_char);

t_token	*ft_lexer(char *input)
{
	t_lexer lexer;
	lexer.input = input;
	lexer.i = 0;
	lexer.state = LEXER_DEFAULT;
	lexer.tokens = NULL;
	lexer.buff_idx = 0;
	while(lexer.input[lexer.i])
	{
		ft_process_char(&lexer, lexer.input[lexer.i]);
		lexer.i++;
	}
	return (lexer.tokens);
}

static void ft_process_char(t_lexer *lx, char current_char)
{
	if (lx->state == LEXER_DEFAULT)
		ft_handle_default_state(lx, current_char);
	else if (lx->state == LEXER_IN_SING_QUOTE)
		ft_handle_single_quote_state(lx, current_char);
	else if (lx->state == LEXER_IN_DOUBLE_QUOTE)
		ft_handle_double_quote_state(lx, current_char);
}