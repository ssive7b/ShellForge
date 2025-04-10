/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:36:33 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/10 22:09:52 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "ast_mock.h"

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

void	print_ast2(int j, t_ast_node *n, t_list *re, t_redir *r)
{
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
		while(re)
		{
			r = re->content;
			printf("   Redirection: type: %d file: %s\n");
			r->type;
			if (r->file_name)
				printf("%s\n", r->file_name);
			else
				printf("%s\n", r->delimiter_heredoc);
			r = re->next;
		}
	}
}

void	print_ast(t_ast_node *node, int level)
{
	t_list	*redirections;
	t_redir	*redir;
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
	redirections = node->redirections;
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
		if (redirections)
		{
			while(redirections)
			{
				redir = redirections->content;
				printf("   Redirection: type: %d file: %s\n",
				redir->type,
				redir->file_name ? redir->file_name : redir->delimiter_heredoc);
				redirections = redirections->next;
			}
		}
	}
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
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}
