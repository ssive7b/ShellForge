/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:28:58 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/24 11:29:00 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast_mock.h"
#include "minishell.h"
#include "env_utils.h"

void	exec_env(t_ast_node *node, t_list *env_list)
{
	t_list	*env_node_current;
	t_env	*env_entry;

	env_node_current = env_list;
	while(env_node_current)
	{
		env_entry = env_node_current->content;
		if (env_entry->value && *env_entry->value)
		{
			ft_putstr_fd(env_entry->key, node->fd_out);
			ft_putstr_fd("=", node->fd_out);
			ft_putstr_fd(env_entry->value, node->fd_out);
			ft_putstr_fd("\n", node->fd_out);
		}
		env_node_current = env_node_current->next;
	}
}