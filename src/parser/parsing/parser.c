#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

static int	process_token(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
static int	process_command_token(t_lexer *lexer, t_ast_stack **operand_stack);
static int	process_operator_token(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
static int	finalize_ast(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_lexer *lexer, t_ast_node **ast_root);

t_ast_node	*parse_tokens(t_lexer *lexer)
{
    t_ast_stack	*operator_stack = NULL;
    t_ast_stack	*operand_stack = NULL;
    t_ast_node	*ast_root = NULL;

    while (lexer->tokens)
    {
        if (!process_token(lexer, &operator_stack, &operand_stack))
            return (NULL);
    }
    if (!finalize_ast(&operator_stack, &operand_stack, lexer, &ast_root))
        return (NULL);
    return (ast_root);
}

static int	process_token(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    if (is_command_token(lexer->tokens->type))
        return (process_command_token(lexer, operand_stack));
    else if (is_operator_token(lexer->tokens->type))
        return (process_operator_token(lexer, operator_stack, operand_stack));
    else if (lexer->tokens->type == TOKEN_LPAREN)
        return (handle_left_parenthesis(lexer, operator_stack));
    else if (lexer->tokens->type == TOKEN_RPAREN)
        return (handle_right_parenthesis(lexer, operator_stack, operand_stack));
    else if (lexer->tokens->type == TOKEN_DELIMITER)
    {
        advance_token(lexer);
        return (1);
    }
    else
    {
        perror("Syntax error: unexpected token");
        lexer->error = 1;
        return (0);
    }
}

static int	process_command_token(t_lexer *lexer, t_ast_stack **operand_stack)
{
    t_ast_node	*command_node;
	
	command_node = parse_command(lexer);
    if (!command_node)
        return (0);
    push_ast_stack(operand_stack, command_node);
	print_stack(*operand_stack, "stack_after_command");
    return (1);
}

static int	process_operator_token(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    handle_operator(lexer, operator_stack, operand_stack);
    return (1);
}

static int	finalize_ast(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_lexer *lexer, t_ast_node **ast_root)
{
    while (*operator_stack)
    {
        if (!process_operator(operator_stack, operand_stack))
        {
            perror("Error: Failed to process operator");
            lexer->error = 1;
            return (0);
        }
    }
    *ast_root = pop_ast_stack(operand_stack);
    if (*operand_stack)
    {
        fprintf(stderr, "%d\n", (*operand_stack)->node->type);
        perror("Syntax error: invalid expression");
        lexer->error = 1;
        return (0);
    }
    return (1);
}