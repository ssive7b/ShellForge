/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:03:50 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/25 21:03:51 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"
#include "executioner.h"
#include "utils.h"

static char	*format_env_entry(t_env *env_entry);

void	update_env_entry(t_env *existing_entry, char *value)
{
	free(existing_entry->value);
	existing_entry->value = value;
}

void	add_env_entry(char *key, char *value, t_list *env_list)
{
	t_list	*new_node;

	new_node = create_env_node(key, value);
	ft_lstadd_back(&env_list, new_node);
}

char	**get_sorted_env(t_list *env_list)
{
	t_list	*env_node;
	char	**sorted_env_array;
	size_t	i;
	size_t	env_size;

	env_size = ft_lstsize(env_list);
	sorted_env_array = malloc (sizeof(char *) * (env_size + 1));
	if (!sorted_env_array)
		return (NULL);
	env_node = env_list;
	i = 0;
	while (env_node)
	{
		sorted_env_array[i] = format_env_entry(env_node->content);
		env_node = env_node->next;
		i++;
	}
	sorted_env_array[i] = NULL;
	ft_bubble_sort(sorted_env_array, env_size);
	return (sorted_env_array);
}

void	print_sorted_env(t_anode *node, char **sorted_env_array)
{
	size_t	i;

	i = 0;
	while (sorted_env_array[i])
	{
		ft_putstr_fd("declare -x ", node->fd_out);
		ft_putstr_fd(sorted_env_array[i], node->fd_out);
		ft_putstr_fd("\n", node->fd_out);
		free(sorted_env_array[i]);
		sorted_env_array[i] = NULL;
		i++;
	}
	free(sorted_env_array);
	sorted_env_array = NULL;
}

static char	*format_env_entry(t_env *env_entry)
{
	char	*val;
	char	*res;
	bool	need_free;

	if (!env_entry->value)
		return (ft_strdup(env_entry->key));
	need_free = false;
	if (*env_entry->value == '\0')
		val = "\"\"";
	else
	{
		val = ft_strjoin_multiple((char *[]){"\"", env_entry->value, "\""}, 3);
		if (!val)
			return (NULL);
		need_free = true;
	}
	res = ft_strjoin_multiple((char *[]){env_entry->key, "=", val}, 3);
	if (need_free)
		safe_free((void **)&val);
	return (res);
}
