#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

int	main(void)
{
	char	*input;

	while(1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}