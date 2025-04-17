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

void	node_free(t_anode **node)
{
	size_t	i;

	if (!node || !*node)
		return ;
	if ((*node)->left)
		node_free(&(*node)->left);
	if ((*node)->right)
		node_free(&(*node)->right);
	if ((*node)->type == NODE_COMMAND)
	{
		safe_free((void **)&(*node)->cmd_pathname);
		if ((*node)->args)
		{
			i = 0;
			while ((*node)->args[i])
			{
				safe_free((void **)&(*node)->args[i]);
				i++;
			}
			safe_free((void **)&(*node)->args);
		}
	}
	if ((*node)->redirs)
		clr_redirs(&(*node)->redirs);
	safe_free((void **)node);
}

void	stack_free(t_stack **stack)
{
	t_stack	*current;
	t_stack	*next;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		node_free(&current->node);
		safe_free((void **)&current);
		current = next;
	}
	*stack = NULL;
}

void	parser_cleanup(t_stack **ops, t_stack **opnds, t_anode **node)
{
	if (opnds)
		stack_free(ops);
	if (opnds)
		stack_free(opnds);
	if (node && *node)
		node_free(node);
}

void	clr_redirs(t_list **redirs)
{
	if (!redirs)
		return ;
	ft_lstclear(redirs, del_redir);
}

void	del_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (redir->file_name)
		safe_free((void **)&redir->file_name);
	if (redir->delimiter_heredoc)
		safe_free((void **)&redir->delimiter_heredoc);
	safe_free((void **)&redir);
}
