#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "lexer.h"

int	main(void)
{
	char	*input;

	while(1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		if (*input)
		{
			ft_print_tokens(ft_lexer(input));
			add_history(input);
		}
		free(input);
	}
	return (0);
}