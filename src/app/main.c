#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_tty				minish;
	t_token				*tokens;
	t_ast_node			*ast_root;
	t_lexer				lexer;
	t_expand_context	context;

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
				ft_error_msg("Error: Lexer returned NULL");
				return (1);
			}
			context.env_list = minish.env_list;
			context.last_exit_status = minish.exit_status;
			if (!expand_variables_in_tokens(&tokens, &context))
			{
				ft_error_msg("Error: Variable expansion failed");
				free_tokens(tokens);
				return (2);
			}
			// ft_print_tokens(tokens); 
			lexer.tokens = tokens;
			lexer.error = 0;
			ast_root = parse_tokens(&lexer);
			if (!ast_root)
			{
				ft_error_msg("Parser returned NULL");
				free_tokens(tokens);
				return (3);
			}
			// print_ast(ast_root, 0); // Debugging: Print AST
			add_history(minish.line);
			exec_astree(&minish, ast_root);

			free_ast_node(&ast_root);
			free_tokens(tokens);
		}
		free(minish.line);
	}
	return (0);
}