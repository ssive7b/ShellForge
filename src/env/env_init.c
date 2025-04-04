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

t_list	**get_env(void)
{
	static t_list	*env = NULL;

	return (&env);
}

void	init_env(char **envp)
{
	t_list	*env_list;
	t_list	*env_node;
	size_t	i;

	if (!envp)
		return ;
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_node = to_env_node(envp[i]);
		ft_lstadd_back(&env_list, env_node);
		i++;
	}
	*get_env() = env_list;
}


