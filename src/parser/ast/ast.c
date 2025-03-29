#include "ast_mock.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

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
		new->cmd_pathname = token->value;
	return (new);
}

int	get_operator_precedence(t_node_type type)
{
	if (type == NODE_PIPE)
		return (1);
	if (type == NODE_OR || type == NODE_AND)
		return (2);
	if (type == NODE_REDIRECTION)
		return (3);
	return (0);
}

void	push_ast_stack(t_ast_stack **stack, t_ast_node *node)
{
	t_ast_stack	*new_node;
	t_ast_stack	*temp;

	new_node = malloc(sizeof(t_ast_stack));
	if (!new_node)
		return ;
	new_node->node = node;
	new_node->next = NULL;
	if (*stack == NULL)
		*stack = new_node;
	else
	{
		temp = *stack;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
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
	free(current);
	return (node);
}

// Process operators and build subtrees
void	process_operator(t_ast_stack **op_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*op_node;

	if (!op_stack || !*op_stack)
		return ;
	op_node = pop_ast_stack(op_stack);
	if (!op_node)
		return ;
	op_node->right = pop_ast_stack(operand_stack);
	op_node->left = pop_ast_stack(operand_stack);
	push_ast_stack(operand_stack, op_node);
}

// Build AST from tokens
t_ast_node	*construct_ast(t_token *tokens)
{
	t_ast_stack	*operand_stack;
	t_ast_stack	*op_stack;
	t_ast_node	*cmd_node;
	t_node_type	op_type;
	t_ast_node	*root;

	operand_stack = NULL;
	op_stack = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD_UNQUOTED
			|| tokens->type == TOKEN_WORD_DQUOTED
			|| tokens->type == TOKEN_WORD_SQUOTED)
		{
			cmd_node = ast_new(NODE_COMMAND, tokens);
			if (cmd_node)
				push_ast_stack(&operand_stack, cmd_node);
		}
		else
		{
			op_type = get_ast_node_type_from_token(tokens->type);
			// Convert token type to AST node type
			while (op_stack
				&& get_operator_precedence(op_stack->node->type) >= get_operator_precedence(op_type))
				process_operator(&op_stack, &operand_stack);
			push_ast_stack(&op_stack, ast_new(op_type, tokens));
		}
		tokens = tokens->next;
	}
	while (op_stack)
		process_operator(&op_stack, &operand_stack);
	root = pop_ast_stack(&operand_stack);
	if (!root)
		printf("AST construction failed: operand stack was empty\n");
	return (root);
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

	if (!node)
		return ;
	i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
	if (node->type == NODE_COMMAND)
		printf("CMD: %s\n", node->cmd_pathname);
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
