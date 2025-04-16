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

#include <stdio.h>
#include "utils.h"
#include "ast_mock.h"

static void	print_node_type(t_anode *node, int level);
static void	print_command_node(t_anode *node, int level);
static void	print_redirections(t_list *redirections, int level);

void	print_stack(t_stack *stack, const char *name)
{
	printf("Stack %s:\n", name);
	while (stack)
	{
		printf("  Node type: %d\n", stack->node->type);
		printf("  Node pathname: %s\n", stack->node->cmd_pathname);
		stack = stack->next;
	}
}

void	print_ast(t_anode *node, int level)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		print_command_node(node, level);
	else
		print_node_type(node, level);
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

static void	print_node_type(t_anode *node, int level)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i++ < level)
		ft_printf(" ");
	if (node->type == NODE_PIPE)
		ft_printf("PIPE\n");
	else if (node->type == NODE_AND)
		ft_printf("AND\n");
	else if (node->type == NODE_OR)
		ft_printf("OR\n");
	else if (node->type == NODE_REDIRECTION)
	{
		redir = node->redirections->content;
		ft_printf("Redirection: %d\n", redir->type);
	}
}

static void	print_command_node(t_anode *node, int level)
{
	int		i;
	int		j;
	t_list	*redirections;

	i = 0;
	while (i++ < level)
		ft_printf(" ");
	j = 0;
	ft_printf("CMD: ");
	while (node->args[j])
	{
		ft_printf("%s ", node->args[j]);
		j++;
	}
	ft_printf("\n");
	redirections = node->redirections;
	if (redirections)
		print_redirections(redirections, level + 1);
}

static void	print_redirections(t_list *redirections, int level)
{
	t_redir	*redir;
	int		i;

	while (redirections)
	{
		redir = redirections->content;
		i = 0;
		while (i++ < level)
			ft_printf(" ");
		if (redir->file_name)
			ft_printf("Redirection: type: %d file: %s\n", redir->type,
				redir->file_name);
		else
			ft_printf("Redirection: type: %d file: %s\n", redir->type,
				redir->delimiter_heredoc);
		redirections = redirections->next;
	}
}
