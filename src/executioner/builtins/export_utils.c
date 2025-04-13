/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:03:50 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:46:12 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "env_utils.h"
#include "executioner.h"
#include "minishell.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

void	update_existing_env_entry(t_env *existing_entry, char *value)
{
	free(existing_entry->value);
	existing_entry->value = value;
}

void	add_new_env_entry(char *key, char *value, t_list *env_list)
{
	t_list	*new_node;

	new_node = create_new_env_node(key, value);
	ft_lstadd_back(&env_list, new_node);
}

char	**get_sorted_env_array(t_list *env_list)
{
	t_list	*env_node;
	t_env	*env_entry;
	char	**sorted_env_array;
	size_t	i;
	size_t	env_size;

	env_size = ft_lstsize(env_list);
	sorted_env_array = malloc(sizeof(char *) * (env_size + 1));
	if (!sorted_env_array)
		return (NULL);
	env_node = env_list;
	i = 0;
	while (env_node)
	{
		env_entry = env_node->content;
		if (env_entry->value)
		{
			if (*env_entry->value == '\0')
				sorted_env_array[i] = ft_strjoin_multiple((char *[]){env_entry->key,
						"=", "\"\""}, 3);
			else
				sorted_env_array[i] = ft_strjoin_multiple((char *[]){env_entry->key,
						"=", env_entry->value}, 3);
		}
		else
			sorted_env_array[i] = ft_strdup(env_entry->key);
		env_node = env_node->next;
		i++;
	}
	sorted_env_array[i] = NULL;
	ft_bubble_sort(sorted_env_array, env_size);
	return (sorted_env_array);
}

void	print_sorted_env_list(t_ast_node *node, char **sorted_env_array)
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
