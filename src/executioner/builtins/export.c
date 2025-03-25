/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:48:35 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/25 10:48:36 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"
#include "executioner.h"

static void	print_no_args_case(t_ast_node *node, t_list *env_list);
static bool	is_valid_export_expr(const char *str);
static void	export_var(char *var, t_list *env_list);

void	exec_export(t_ast_node *node)
{
	size_t	i;

	if (!node->args[1])
	{
		print_no_args_case(node, *get_env());
		return ;
	}
	i = 0;
	while (node->args[++i])
	{
		if (!is_valid_export_expr(node->args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			node->exit_status = 1;
			continue ;
		}
		export_var(node->args[i], *get_env());
	}
	exec_env(node, *get_env());
}

static void	print_no_args_case(t_ast_node *node, t_list *env_list)
{
	t_list	*env_node_current;
	t_env	*env_entry;

	env_node_current = env_list;
	while (env_node_current)
	{
		env_entry = env_node_current->content;
		ft_putstr_fd("declare -x ", node->fd_out);
		ft_putstr_fd(env_entry->key, node->fd_out);
		if (env_entry->value)
		{
			ft_putstr_fd("=\"", node->fd_out);
			ft_putstr_fd(env_entry->value, node->fd_out);
			ft_putstr_fd("\"", node->fd_out);
		}
		ft_putstr_fd("\n", node->fd_out);
		env_node_current = env_node_current->next;
	}
}

static bool	is_valid_export_expr(const char *str)
{
	size_t	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (true);
	return (false);
}


static void	export_var(char *var, t_list *env_list)
{
	t_list	*new_node;

	new_node = to_env_node(var);
	if (!new_node)
	{
		if (get_envp_value(var, env_list))
			return ;
		new_node = create_new_env_node(ft_strdup(var), ft_strdup(""));
	}
	ft_lstadd_back(&env_list, new_node);
}
