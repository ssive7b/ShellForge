#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_tty minish;
	t_token *tokens;
	t_ast_node *ast_root;

	(void)argc;
	(void)argv;
	init_minishell(&minish, envp);
	while (1)
	{
		minish.line = readline(minish.prompt);
		if (!minish.line)
		{
			printf("breaking\n");
			break ;
		}
		if (*minish.line)
		{
			tokens = ft_lexer(minish.line);
			if (!tokens)
			{
				printf("Lexer returned NULL\n");
				return (1);
			}
			expand_tokens(tokens, minish.envp, minish.exit_status);
			ft_print_tokens(tokens); // Debugging: Print tokens
			ast_root = construct_ast(tokens);
			print_ast(ast_root, 0); // Debugging: Print AST
			add_history(minish.line);
		}
		exec_astree(&minish, ast_root);
		free(minish.line);
	}
	return (0);
}