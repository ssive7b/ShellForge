/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:45 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/19 14:03:47 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*to_env_node(char *env_string)
{
	t_list	*env_node;
	t_env	*env_entry;
	char	*ptr_eq;
	size_t	idx_eq;

	if (!env_string)
		return (NULL);
	env_entry = malloc(sizeof(t_env));
	if (!env_entry)
		return (NULL);
	ptr_eq = ft_strchr(env_string, '=');
	if (!ptr_eq)
		return (NULL);
	idx_eq = ptr_eq - env_string;
	env_entry->key = ft_substr(env_string, 0, idx_eq);
	env_entry->value = ft_substr(env_string, idx_eq + 1, ft_strlen(env_string) - idx_eq - 1);
	env_node = ft_lstnew((t_env *)env_entry);
	if (!env_node)
		return (NULL);
	return (env_node);
}

/*
char	*ft_find_key_paths(char *key, t_list *env_list)
{
	int	key_len;

	if (!env_list)
		return (NULL);
	key_len = ft_strlen(key);
	while (*dirp)
	{
		if (ft_strncmp(key, *dirp, key_len) == 0 && (*dirp)[key_len] == '=')
			return (*dirp + key_len + 1);
		dirp++;
	}
	return (NULL);
}

char	**ft_split_key_paths(char **dirp)
{
	char	*path;

	if (!dirp)
		return (NULL);
	path = ft_find_key_paths("PATH", dirp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*ft_find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	paths = ft_split_key_paths(envp);
	if (!paths || !(*paths))
		paths = ft_split(".", ' ');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			break ;
		full_path = ft_get_full_path(path, cmd);
		free(path);
		if (!full_path)
			break ;
		if (access(full_path, F_OK) == 0)
			return (ft_free_2d_array(paths, -1), full_path);
		free(full_path);
	}
	return (ft_free_2d_array(paths, -1), NULL);
}
*/