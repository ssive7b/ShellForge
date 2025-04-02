#include "ast_mock.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Create new AST nodes
t_ast_node	*ast_new(t_node_type type, t_token *token)
{
    t_ast_node	*new;

    if (!token)
    {
		ft_error_msg("Error: ast_new received NULL token");
        return (NULL);
    }
    new = malloc(sizeof(t_ast_node));
    if (!new)
        return (NULL);
    new->type = type;
    new->cmd_pathname = NULL;
    new->args = NULL;
    new->pid = -1;
    new->fd_in = -1;
    new->fd_out = -1;
    new->exit_status = 0;
    new->redir = NULL;
    new->left = NULL;
    new->right = NULL;
    if (type == NODE_COMMAND)
    {
		new->cmd_pathname = ft_strdup(token->value);
		if (!new->cmd_pathname)
		{
			safe_free((void **)&new);
			return (NULL);
		}
        new->args = malloc(2 * sizeof(char *));
        if (!new->args)
        {
			safe_free((void **)&new->cmd_pathname);
            safe_free((void **)&new);
			ft_error_msg("Error: Memory allocation failed for args in ast_new");
            return (NULL);
        }
        new->args[0] = ft_strdup(token->value);
		if (!new->args[0])
		{
			safe_free((void **)&new->args);
			safe_free((void **)&new->cmd_pathname);
            safe_free((void **)&new);
			return (NULL);
		}
        new->args[1] = NULL;
    }
    return (new);
}

int	get_operator_precedence(t_node_type type)
{
	if (type == NODE_LPAREN || type == NODE_RPAREN)
		return (3);
	else if (type == NODE_REDIRECTION)
		return (2);
	else if (type == NODE_PIPE)
		return (1);
	else if (type == NODE_AND || type == NODE_OR)
		return (0);
	return (-1);
}

int	push_ast_stack(t_ast_stack **stack, t_ast_node *node)
{
	t_ast_stack	*new_node;

	new_node = malloc(sizeof(t_ast_stack));
	if (!new_node)
		return (0);
	new_node->node = node;
	new_node->next = *stack;
	*stack = new_node;
	return (1);
}

t_ast_node	*pop_ast_stack(t_ast_stack **stack)
{
	t_ast_stack	*current;
	t_ast_node	*node;

	current = *stack;
	if (current == NULL)
		return (NULL);
	node = current->node;
	*stack = current->next;
	safe_free((void **)&current);
	return (node);
}

bool	process_operator(t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    t_ast_node	*op_node;
	t_ast_node	*right_operand;
	t_ast_node	*left_operand;

    if (!operator_stack || !(*operator_stack) || !operand_stack)
		return (false);
	if (!*operand_stack || !(*operand_stack)->next)
	{
		ft_error_msg("Error: Not enough operands for operator");
		return (false);
	}
    op_node = pop_ast_stack(operator_stack);
    if (!op_node)
		return (false);
	right_operand = pop_ast_stack(operand_stack);
	left_operand = pop_ast_stack(operand_stack);
    op_node->right = right_operand;
    op_node->left = left_operand;
    push_ast_stack(operand_stack, op_node);
    return (true);
}

t_node_type	get_ast_node_type_from_token(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (type == TOKEN_OR)
		return (NODE_OR);
	if (type == TOKEN_AND)
		return (NODE_AND);
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC)
		return (NODE_REDIRECTION);
	return (NODE_COMMAND);
}
