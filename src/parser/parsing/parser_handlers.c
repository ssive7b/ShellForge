#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*node;

	if (!lexer->tokens || !is_command_token(lexer->tokens->type))
	{
		perror("Syntax error: expected command");
		lexer->error = 1;
		return (NULL);
	}
	node = ast_new(NODE_COMMAND, lexer->tokens);
	if (!node)
		return (NULL);
	advance_token(lexer);
	while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
		advance_token(lexer);
	while (lexer->tokens && is_argument_token(lexer->tokens->type))
	{
		add_argument_to_node(node, lexer->tokens->value);
		advance_token(lexer);
		while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
			advance_token(lexer);
	}
	return (node);
}

int	handle_operator(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    t_node_type	op_type;
	t_ast_node	*op_node;
	
	op_type = get_ast_node_type_from_token(lexer->tokens->type);
    while (*operator_stack
		&& (*operator_stack)->node->type != NODE_LPAREN
		&& get_operator_precedence((*operator_stack)->node->type) >= get_operator_precedence(op_type))
	{
		if (!process_operator(operator_stack, operand_stack))
		{
			perror("Error: Failed to process operator");
			lexer->error = 1;
			return (0);
		}
	}
	op_node = ast_new(op_type, lexer->tokens);
	if (!op_node)
	{
		perror("Error: Memory allocation failed for operator node");
		lexer->error = 1;
		return (0);
	}
    push_ast_stack(operator_stack, op_node);
    advance_token(lexer);
	return (1);
}

int handle_left_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack)
{
    t_ast_node *left_paren_node;
	
	left_paren_node = ast_new(NODE_LPAREN, lexer->tokens);
    if (!left_paren_node)
    {
        fprintf(stderr, "Error: Memory allocation failed for left parenthesis\n");
        lexer->error = 1;
        return 0;
    }
    push_ast_stack(operator_stack, left_paren_node);
    advance_token(lexer); // Move to the next token
    return 1;
}

int handle_right_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*left_paren;

    while (*operator_stack && (*operator_stack)->node->type != NODE_LPAREN)
    {
        if (!process_operator(operator_stack, operand_stack))
        {
            fprintf(stderr, "Error: Failed to process operator inside parentheses\n");
            lexer->error = 1;
            return 0;
        }
    }
    if (!*operator_stack || (*operator_stack)->node->type != NODE_LPAREN)
    {
        fprintf(stderr, "Syntax error: unmatched right parenthesis\n");
        lexer->error = 1;
        return 0;
    }
	left_paren = pop_ast_stack(operator_stack);
	free_ast_node(left_paren);
    advance_token(lexer);
    return (1);
}