/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:36:22 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/19 13:36:23 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "../libft/include/libft.h"
#include "env_utils.h"
#include "utils.h"

t_list	*create_minimal_env(void)
{
	t_list	*env_list;
	t_list	*env_node;
	char	*key;
	char	*value;

	env_list = NULL;
	key = ft_strdup("SHELL");
	if (!key)
		return (NULL);
	value = ft_strdup("1");
	if (!value)
	{
		safe_free((void **)&key);
		return (NULL);
	}
	env_node = create_env_node(key, value);
	if (!env_node)
	{
		safe_free((void **)&key);
		safe_free((void **)&value);
		return (NULL);
	}
	ft_lstadd_back(&env_list, env_node);
	return (env_list);
}
