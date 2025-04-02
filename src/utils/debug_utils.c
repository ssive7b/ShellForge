/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:36:33 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 23:36:34 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_stack(t_ast_stack *stack, const char *name)
{
	printf("Stack %s:\n", name);
	while (stack)
	{
		printf("  Node type: %d\n", stack->node->type);
		printf("  Node pathname: %s\n", stack->node->cmd_pathname);
		stack = stack->next;
	}
}

void	print_ast(t_ast_node *node, int level)
{
	int	i;
	int j;

	if (!node)
		return ;
	i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
	if (node->type == NODE_COMMAND)
	{
		j = 0;
		printf("CMD: ");
		while (node->args[j])
		{
			printf("%s ", node->args[j]);
			j++;
		}
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_AND)
		printf("AND\n");
	else if (node->type == NODE_OR)
		printf("OR\n");
	else if (node->type == NODE_REDIRECTION)
		printf("Redirection: %d\n", node->redir->type);
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}