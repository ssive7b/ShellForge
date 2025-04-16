/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:36:22 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/26 15:36:23 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"
#include "executioner.h"
#include "utils.h"

static void	exec_cd_home(t_anode *node, char *oldpwd);
static void	update_env_var(char *key, char *value);
static void	handle_cd_error(t_anode *node, char *path);

void	exec_cd(t_anode *node)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!node->args[1])
	{
		exec_cd_home(node, cwd);
		free(cwd);
		return ;
	}
	if (chdir(node->args[1]) == 0)
	{
		update_env_var("OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(NULL, 0);
		update_env_var("PWD", cwd);
		free(cwd);
		node->exit_status = 0;
	}
	else
	{
		handle_cd_error(node, node->args[1]);
		free(cwd);
	}
}

static void	exec_cd_home(t_anode *node, char *oldpwd)
{
	char	*path_home;
	char	*new_cwd;

	path_home = ft_strdup(get_envp_value("HOME", *get_env()));
	if (!path_home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		node->exit_status = 1;
		return ;
	}
	if (chdir(path_home) == 0)
	{
		update_env_var("OLDPWD", oldpwd);
		new_cwd = getcwd(NULL, 0);
		update_env_var("PWD", new_cwd);
		free(new_cwd);
		node->exit_status = 0;
	}
	else
		handle_cd_error(node, path_home);
	free(path_home);
}

static void	update_env_var(char *key, char *value)
{
	t_list	*current_env_node;
	t_list	*new_env_node;
	t_env	*env_entry;

	if (!value)
		return ;
	current_env_node = *get_env();
	env_entry = get_env_entry(key, current_env_node);
	if (env_entry)
	{
		free(env_entry->value);
		env_entry->value = ft_strdup(value);
	}
	else
	{
		new_env_node = create_new_env_node(ft_strdup(key), ft_strdup(value));
		ft_lstadd_back(&current_env_node, new_env_node);
	}
}

static void	handle_cd_error(t_anode *node, char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	node->exit_status = 1;
}
