#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/limits.h>
#include "lexer.h"
#include "env_utils.h"
#include "minishell.h"
#include "executioner.h"

int	main(int argc, char **argv, char **envp)
{
	t_tty	minish;

	(void)argc;
	(void)argv;
	init_minishell(&minish, envp);
	while(1)
	{
		minish.line = readline(minish.prompt);
		if (!minish.line)
		{
			printf("breaking\n");
			break ;
		}
		if (*minish.line)
		{
			ft_print_tokens(ft_lexer(minish.line));
			add_history(minish.line);
		}
		exec_astree(&minish, minish.ast_tree);
		free(minish.line);
	}
	return (0);
}