/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:45 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/03 14:00:11 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"
#include "utils.h"

t_list	*to_env_node(char *env_str)
{
	t_list	*env_node;
	t_env	*env_entry;
	char	*ptr_eq;
	size_t	idx_eq;

	if (!env_str)
		return (NULL);
	env_entry = malloc(sizeof(t_env));
	if (!env_entry)
		return (NULL);
	ptr_eq = ft_strchr(env_str, '=');
	if (!ptr_eq)
		return (NULL);
	idx_eq = ptr_eq - env_str;
	env_entry->key = ft_substr(env_str, 0, idx_eq);
	env_entry->value = ft_strdup(env_str + idx_eq + 1);
	env_node = ft_lstnew((t_env *)env_entry);
	if (!env_node)
		return (NULL);
	return (env_node);
}

char	*get_envp_value(char *key, t_list *env_list)
{
	char	*value;
	t_list	*current_envp;
	t_env	*env_entry;

	if (!env_list)
		return (NULL);
	current_envp = env_list;
	value = NULL;
	while (current_envp)
	{
		env_entry = current_envp->content;
		if (ft_strcmp(key, env_entry->key) == 0)
		{
			value = env_entry->value;
			break ;
		}
		current_envp = current_envp->next;
	}
	return (value);
}

t_env	*get_env_entry(char *key, t_list *env_list)
{
	t_list	*current_env_node;
	t_env	*env_entry;

	current_env_node = env_list;
	while (current_env_node)
	{
		env_entry = current_env_node->content;
		if (ft_strcmp(env_entry->key, key) == 0)
			return (env_entry);
		current_env_node = current_env_node->next;
	}
	return (NULL);
}

t_list	*create_new_env_node(char *key, char *value)
{
	t_list	*env_node;
	t_env	*env_entry;

	env_entry = malloc(sizeof(t_env));
	if (!env_entry)
		return (NULL);
	env_entry->key = key;
	env_entry->value = value;
	env_node = ft_lstnew((t_env *)env_entry);
	if (!env_node)
		return (NULL);
	return (env_node);
}
