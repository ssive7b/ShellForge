/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:20:27 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/04 15:20:29 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell				minish;
	t_token				*tokens;
	t_ast_node			*ast_root;
	t_lexer				lexer;
	t_expand_context	context;

	if (argc != 1 || argv[1])
		return (1);
	init_env(envp);
	init_minishell(&minish, envp);
	while (1)
	{
		minish.line = readline(minish.prompt);
		if (!minish.line)
		{
			ft_error_msg("Error: Unable to read the line");
			break ;
		}
		if (*minish.line)
		{
			tokens = ft_lexer(minish.line);
			if (!tokens)
			{
				ft_error_msg("Error: Lexer returned NULL");
				return (2);
			}
			context.env_list = minish.env_list;
			context.last_exit_status = minish.exit_status;
			if (!expand_variables_in_tokens(&tokens, &context))
			{
				ft_error_msg("Error: Variable expansion failed");
				free_tokens(tokens);
				return (3);
			}
			ft_print_tokens(tokens); // Debugging: Print Tokens
			lexer.tokens = tokens;
			lexer.error = 0;
			ast_root = parse_tokens(&lexer);
			if (!ast_root)
			{
				ft_error_msg("Parser returned NULL");
				free_tokens(tokens);
				return (4);
			}
			print_ast(ast_root, 0); // Debugging: Print AST
			add_history(minish.line);
			exec_astree(&minish, ast_root);

			free_ast_node(&ast_root);
			free_tokens(tokens);
		}
		free(minish.line);
	}
	return (0);
}
