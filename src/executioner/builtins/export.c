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
#include "char_designation.h"
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"
#include "executioner.h"
#include "utils.h"

static void	print_no_args_case(t_anode *node, t_list *env_list);
static bool	is_valid_export_expr(const char *str);
static void	export_var(char *var, t_list *env_list);

void	exec_export(t_anode *node)
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
}

static void	print_no_args_case(t_anode *node, t_list *env_list)
{
	char	**sorted_env_array;

	sorted_env_array = get_sorted_env(env_list);
	if (!sorted_env_array)
		return ;
	print_sorted_env(node, sorted_env_array);
}

static bool	is_valid_export_expr(const char *str)
{
	size_t	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (is_valid_var_char(str[i]))
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (true);
	return (false);
}

static void	export_var(char *var, t_list *env_list)
{
	t_env	*existing_entry;
	int		eq_index;
	char	*key;
	char	*value;

	eq_index = ft_find_char(var, '=');
	if (eq_index == -1)
	{
		if (!get_env_entry(var, env_list))
			ft_lstadd_back(&env_list, create_env_node(ft_strdup(var), NULL));
		return ;
	}
	key = ft_substr(var, 0, eq_index);
	value = ft_strdup(var + eq_index + 1);
	existing_entry = get_env_entry(key, env_list);
	if (existing_entry)
	{
		update_env_entry(existing_entry, value);
		safe_free((void **)&key);
	}
	else
		add_env_entry(key, value, env_list);
}
