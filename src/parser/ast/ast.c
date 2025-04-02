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
        printf("Error: ast_new received NULL token\n");
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
        new->cmd_pathname = token->value;
        new->args = malloc(2 * sizeof(char *));
        if (!new->args)
        {
            safe_free((void **)&new);
            printf("Error: Memory allocation failed for args in ast_new\n");
            return (NULL);
        }
        new->args[0] = token->value;
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

    if (!operator_stack || !*operator_stack)
        return (false);
    op_node = pop_ast_stack(operator_stack);
    if (!op_node)
        return (false);
    op_node->right = pop_ast_stack(operand_stack);
    op_node->left = pop_ast_stack(operand_stack);
    if (!op_node->right || !op_node->left)
    {
        perror("Error: Not enough operands for operator");
        return (false);
    }
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

// Just for debugging
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