/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:21:13 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/20 15:21:14 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

void	ft_free_2d_array(char **array, int n)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while ((n == -1 || i < n) && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_ast_node(t_ast_node *node)
{
	size_t	i;

	i = 0;
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		if (node->cmd_pathname)
			free(node->cmd_pathname);
		if (node->args)
		{
			while(node->args[i])
				free(node->args[i]);
			free(node->args);
		}
	}
	if (node->redir)
	{
		free(node->redir->file_name);
		free(node->redir->delimiter_heredoc);
		free(node->redir);
	}
	free(node);
}

void	free_ast_stack(t_ast_stack **stack)
{
	t_ast_stack	*current;
	t_ast_stack	*next;

	current = *stack;
	while (current)
	{
		next = current->next;
		free_ast_node(current->node);
		free(current);
		current = next;
	}
	*stack = NULL;
}
