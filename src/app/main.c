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

static int	process_cmd_iteration(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1 || argv[1])
		return (1);
	shell = init_minishell(envp);
	while (1)
	{
		shell->input = readline(SHELL_PROMPT);
		if (process_cmd_iteration(shell))
		{
			display_error(shell);
			cleanup_shell(shell);
			return (shell->last_exit_code);
		}
	}
	cleanup_shell(shell);
	return (0);
}

static int	process_cmd_iteration(t_shell *shell)	// prototyping
{
	if (!shell->input || !*(shell->input))
		return (0);
	if (*(shell->input))
		add_history(shell->input);
	shell->tokens = ft_lexer(shell->input);
	if (!shell->tokens)
		return (1);
	if (!expand_variables_in_tokens(shell))
	{
		cleanup_iteration(shell);
		return (1);
	}
	ft_print_tokens(shell->tokens); // Debugging: Print Tokens
	shell->ast_root = parse_tokens(shell);
	if (!shell->ast_root)
	{
		cleanup_iteration(shell);
		return (1);
	}
	print_ast(shell->ast_root, 0); // Debugging: Print AST
	exec_astree(shell);
	cleanup_iteration(shell);
}

