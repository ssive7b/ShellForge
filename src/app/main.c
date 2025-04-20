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
#include "signal_handlers.h"

static bool	process_cmd_iteration(t_shell *sh);
static bool	check_termination_signal(void);

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc != 1 || argv[1])
		return (1);
	shell = init_minishell(envp);
	while (1)
	{
		shell->input = readline(SHELL_PROMPT);
		if (!shell->input || check_termination_signal())
			exit_on_eof(shell);
		if (*(shell->input))
		{
			add_history(shell->input);
			if (!process_cmd_iteration(shell))
				display_error(shell);
		}
		else
			safe_free((void **)&shell->input);
	}
	cleanup_shell(shell);
	return (0);
}

static bool	process_cmd_iteration(t_shell *sh)
{
	if (!sh->input)
	{
		set_error(sh, 1, "Error: Unable to read input");
		return (false);
	}
	sh->ast_root = ast_root(sh->input, sh->env_list, &sh->last_exit_code);
	if (!sh->ast_root && sh->last_exit_code)
	{
		set_error(sh, 1, "Error: Failed while setting up the AST");
		cleanup_iteration(sh);
		return (false);
	}
	exec_ast(sh, sh->ast_root);
	cleanup_iteration(sh);
	return (true);
}

static bool	check_termination_signal(void)
{
	return (g_received_signal == SIGTERM || g_received_signal == SIGQUIT);
}
