/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:02:25 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 14:04:54 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include <stdio.h>
#include <error.h>

static t_ast_node	*get_new_astree(t_tty *minish); // mocking version, change once ast implemented

void	*init_minishell(t_tty *minish, char **envp)
{
	init_env(envp);
	minish->env_list = *get_env();
	minish->cwd = *get_cwd();
	minish->prompt = "minishell$> ";
	minish->line = NULL;
	minish->envp = envp;
	minish->exit_status = 0;
	minish->ast_tree = get_new_astree(minish);
	return (NULL);
}

static t_ast_node	*get_new_astree(t_tty *minish) // mocking version, change once ast implemented
{
	t_ast_node	*new_astree;
	char		**args;

	args = malloc(sizeof(char *) * 3);
	if (!args)
		return (NULL);
	args[0] = "printf";
	args[1] = "main";
	args[2] = NULL;
	new_astree = malloc(sizeof(t_ast_node));
	if (!new_astree)
	{
		perror("new_astree");
		return (NULL);
	}
	new_astree->cmd_pathname = find_exec_pathname(minish, minish->env_list, "echo");
	new_astree->args = args;
	new_astree->fd_in = STDIN_FILENO;
	new_astree->fd_out = STDOUT_FILENO;
	new_astree->redir = NULL;
	new_astree->left = NULL;
	new_astree->right = NULL;
	new_astree->type = NODE_COMMAND;
	return (new_astree);
}