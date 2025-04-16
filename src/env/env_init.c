/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:06 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/19 13:00:07 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "env_utils.h"
#include "utils.h"

t_list	**get_env(void)
{
	static t_list	*env = NULL;

	return (&env);
}

t_list	*create_env_list(char **envp)
{
	t_list	*env_list;
	t_list	*env_node;
	size_t	i;

	if (!envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_node = to_env_node(envp[i]);
		if (!env_node)
		{
			ft_lstclear(&env_list, free_env_content);
			return (NULL);
		}
		ft_lstadd_back(&env_list, env_node);
		i++;
	}
	*get_env() = env_list;
	return (env_list);
}

void	free_env_content(void *content)
{
	t_env	*env_var;

	if (!content)
		return ;
	env_var = (t_env *)content;
	if (env_var->key)
		safe_free((void **)&env_var->key);
	if (env_var->value)
		safe_free((void **)&env_var->value);
	safe_free((void **)&env_var);
}

void	free_env_list(t_list *env_list)
{
	ft_lstclear(&env_list, free_env_content);
}
