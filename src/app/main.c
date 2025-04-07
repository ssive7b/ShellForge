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
#include "signals.h"

static bool	process_cmd_iteration(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1 || argv[1])
		return (1);
	shell = init_minishell(envp);
	setup_interactive_signals();
	while (1)
	{
		shell->input = readline(SHELL_PROMPT);
		if (!process_cmd_iteration(shell))
		{
			display_error(shell);
			cleanup_shell(shell);
			return (shell->last_exit_code);
		}
	}
	cleanup_shell(shell);
	return (0);
}

static bool	process_cmd_iteration(t_shell *shell)	// prototyping
{
	if (!shell->input || !*(shell->input))
	{
		set_error(shell, 1, "Error: Unable to read input");
		return (false);
	}
	if (*(shell->input))
		add_history(shell->input);
	shell->ast_root = get_ast_root(shell->input, shell->env_list, shell->last_exit_code);
	if (!shell->ast_root)
	{
		set_error(shell, 1, "Error: Failed while setting up the AST");
		cleanup_iteration(shell);
		return (false);
	}
	// print_ast(shell->ast_root, 0); // Debugging: Print AST
	exec_astree(shell, shell->ast_root);
	cleanup_iteration(shell);
	return (true);
}

