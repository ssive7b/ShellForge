/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:48:20 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/24 13:48:21 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "char_designation.h"
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"

static bool	is_valid_var_name(const char *var)
{
	size_t	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	i = 1;
	while (var[i])
	{
		if (!is_valid_var_char(var[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	unset_var(const char *var)
{
	t_list	*env_node_current;
	t_list	*env_node_prev;
	t_env	*env_entry;

	env_node_current = *get_env();
	env_node_prev = NULL;
	while (env_node_current)
	{
		env_entry = env_node_current->content;
		if (ft_strcmp(env_entry->key, var) == 0)
		{
			if (env_node_prev)
				env_node_prev->next = env_node_current->next;
			else
				*get_env() = env_node_current->next;
			free(env_entry->key);
			free(env_entry->value);
			free(env_entry);
			free(env_node_current);
			return ;
		}
		env_node_prev = env_node_current;
		env_node_current = env_node_current->next;
	}
}

void	exec_unset(t_anode *node)
{
	size_t	i;

	if (!node->args[1])
	{
		ft_putstr_fd("minishell: unset: too few arguments \n", STDERR_FILENO);
		node->exit_status = 1;
		return ;
	}
	i = 0;
	while (node->args[++i])
	{
		if (!is_valid_var_name(node->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			node->exit_status = 1;
			continue ;
		}
		else
			unset_var(node->args[i]);
	}
}
