#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "lexer.h"
#include "env_utils.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env_list;
	t_env	*env_entry;

	(void)argc;
	(void)argv;
	init_env(envp);
	env_list = *get_env();
	while (env_list)
	{
		env_entry = env_list->content;
		printf("key: <%s>, value: <%s>\n", env_entry->key, env_entry->value);
		env_list = env_list->next;
	}
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