/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mem_cleaners.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:32:56 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/07 21:56:00 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

void	free_ast_node(t_ast_node **node)
{
	size_t	i;

	if (!node || !*node)
		return ;
	if ((*node)->left)
		free_ast_node(&(*node)->left);
	if ((*node)->right)
		free_ast_node(&(*node)->right);
	if ((*node)->type == NODE_COMMAND)
	{
		safe_free((void **)&(*node)->cmd_pathname);
		if ((*node)->args)
		{
			i = 0;
			while((*node)->args[i])
			{
				safe_free((void **)&(*node)->args[i]);
				i++;
			}
			safe_free((void **)&(*node)->args);
		}
	}
	if ((*node)->redirections)
		clear_redirections(&(*node)->redirections);
	safe_free((void **)node);
}

void	free_ast_stack(t_ast_stack **stack)
{
	t_ast_stack	*current;
	t_ast_stack	*next;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		free_ast_node(&current->node);
		safe_free((void **)&current);
		current = next;
	}
	*stack = NULL;
}

void	cleanup_parser_state(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_ast_node **node)
{
	if (operand_stack)
		free_ast_stack(operator_stack);
	if (operand_stack)
		free_ast_stack(operand_stack);
	if (node && *node)
		free_ast_node(node);
}

void	clear_redirections(t_list **redirections)
{
	t_list	*current;
	t_list	*next;

	if (!redirections || !(*redirections))
		return ;
	current = *redirections;
	while (current)
	{
		next = current->next;
		free_redirection((t_redir **)&current->content);
		safe_free((void **)&current);
		current = next;
	}
	*redirections = NULL;
}

void	free_redirection(t_redir **redir)
{
	if (!redir || !(*redir))
		return ;
	if ((*redir)->file_name)
		safe_free((void **)&((*redir)->file_name));
	safe_free((void **)redir);
}
