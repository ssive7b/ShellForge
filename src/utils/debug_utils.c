/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:36:33 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 16:39:21 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include <stdio.h>

void	print_ast(t_ast_node *node, int level);

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

void	print_ast3(t_ast_node *node, int level)
{
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

void	print_ast2(t_ast_node *n, t_list *re, t_redir *r)
{
	int	j;

	j = 0;
	printf("CMD: ");
	while (n->args[j])
	{
		printf("%s ", n->args[j]);
		j++;
	}
	printf("\n");
	if (re)
	{
		while (re)
		{
			r = re->content;
			if (r->file_name)
				printf("   Redirection: type: %d file: %s\n", r->type,
					r->file_name);
			else
				printf("   Redirection: type: %d file: %s\n", r->type,
					r->delimiter_heredoc);
			re = re->next;
		}
	}
}

void	print_ast(t_ast_node *node, int level)
{
	t_list	*redirections;
	t_redir	*redir;
	int		i;

	if (!node)
		return ;
	i = -1;
	while (++i < level)
		printf("  ");
	redirections = node->redirections;
	redir = NULL;
	if (node->type == NODE_COMMAND)
		print_ast2(node, redirections, redir);
	else if (node->type == NODE_PIPE)
		printf("PIPE\n");
	else if (node->type == NODE_AND)
		printf("AND\n");
	else if (node->type == NODE_OR)
		printf("OR\n");
	else if (node->type == NODE_REDIRECTION)
	{
		redir = redirections->content;
		printf("Redirection: %d\n", redir->type);
	}
	print_ast3(node, level);
}
