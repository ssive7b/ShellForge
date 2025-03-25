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

static void	print_no_args_case(t_ast_node *node, t_list *env_list);
static bool	is_valid_export_expr(const char *str);
// static void	export_var(const char *var);

void	exec_export(t_ast_node *node)
{
	size_t	i;

	if (!node->args[1])
	{
		print_no_args_case(node, *get_env());
		return ;
	}
	i = 1;
	while (node->args[i])
	{
		if (!is_valid_export_expr(node->args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(node->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			node->exit_status = 1;
			continue ;
		}
	}

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
		ft_putstr_fd("=\"", node->fd_out);
		ft_putstr_fd(env_entry->value, node->fd_out);
		ft_putstr_fd("\"", node->fd_out);
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
	if (str[i] == '=' || !str[i])
		return (true);
	else
		return (false);
}

/*
static void	export_var(const char *var)
{

}
*/