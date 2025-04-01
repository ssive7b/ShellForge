#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

// Work on error messages!!
static t_ast_node	*parse_command(t_lexer *lexer);
static void			advance_token(t_lexer *lexer);
static int			is_command_token(t_token_type type);
static int			is_operator_token(t_token_type type);
static int			is_argument_token(t_token_type type);
static void			add_argument_to_node(t_ast_node *node, const char *arg);
static void			handle_operator(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
static int 			handle_left_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack);
static int 			handle_right_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);

// Main parser function
t_ast_node	*parse_input(t_lexer *lexer)
{
	t_ast_node	*ast_root;
	t_ast_stack	*operator_stack;
	t_ast_stack	*operand_stack;
	t_ast_node	*command_node;

	ast_root = NULL;
	operator_stack = NULL;
	operand_stack = NULL;
	command_node = NULL;
	while (lexer->tokens)
	{
		if (is_command_token(lexer->tokens->type))
		{
			command_node = parse_command(lexer);
			if (!command_node)
				return (NULL);
			push_ast_stack(&operand_stack, command_node);
		}
		else if (is_operator_token(lexer->tokens->type))
			handle_operator(lexer, &operator_stack, &operand_stack);
        else if (lexer->tokens->type == TOKEN_LPAREN)
        {
            if (!handle_left_parenthesis(lexer, &operator_stack))
                return (NULL);
        }
        else if (lexer->tokens->type == TOKEN_RPAREN)
        {
            if (!handle_right_parenthesis(lexer, &operator_stack, &operand_stack))
                return (NULL);
        }
		else if (lexer->tokens->type == TOKEN_DELIMITER)
			advance_token(lexer);
        else
        {
            perror("Syntax error: unexpected token");
            lexer->error = 1;
            return (NULL);
        }
    }
    while (operator_stack)
	{
		if (!process_operator(&operator_stack, &operand_stack))
		{
			perror("Error: Failed to process operator");
			lexer->error = 1;
			return (NULL);
		}
	}
    ast_root = pop_ast_stack(&operand_stack);
    if (operand_stack)
    {
		fprintf(stderr, "%d\n", operand_stack->node->type);
        perror("Syntax error: invalid expression");
        lexer->error = 1;
        return (NULL);
	}
    return (ast_root);
}

// Parsing a command (e.g., `command arg1 arg2`)
static t_ast_node	*parse_command(t_lexer *lexer)
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
	while (lexer->tokens && is_argument_token(lexer->tokens->type))
	{
		add_argument_to_node(node, lexer->tokens->value);
		advance_token(lexer);
	}
	return (node);
}

// Advance the lexer token
static void	advance_token(t_lexer *lexer)
{
	if (lexer->tokens)
		lexer->tokens = lexer->tokens->next;
}

static int	is_command_token(t_token_type type)
{
    return (type == TOKEN_WORD_UNQUOTED
        || type == TOKEN_WORD_DQUOTED
        || type == TOKEN_WORD_SQUOTED);
}

static int	is_operator_token(t_token_type type)
{
    return (type == TOKEN_PIPE
        || type == TOKEN_AND
        || type == TOKEN_OR
        || type == TOKEN_REDIR_OUT
        || type == TOKEN_REDIR_IN
        || type == TOKEN_REDIR_APPEND
        || type == TOKEN_REDIR_HEREDOC);
}

static int	is_argument_token(t_token_type type)
{
    return (type == TOKEN_WORD_UNQUOTED
        || type == TOKEN_WORD_DQUOTED
        || type == TOKEN_WORD_SQUOTED);
}

static void	add_argument_to_node(t_ast_node *node, const char *arg)
{
    char	**new_args;
    int		arg_count;
    int		i;

    if (!node || !arg)
        return;
    arg_count = 0;
    if (node->args)
    {
        while (node->args[arg_count])
            arg_count++;
    }
    new_args = malloc((arg_count + 2) * sizeof(char *));
    if (!new_args)
    {
        perror("Error: Memory allocation failed in add_argument_to_node");
        return;
    }
	i = -1;
	while (++i < arg_count)
		new_args[i] = node->args[i];
    new_args[arg_count] = ft_strdup(arg);
    if (!new_args[arg_count])
    {
        perror("Error: Memory allocation failed for argument in add_argument_to_node");
        free(new_args);
        return ;
    }
    new_args[arg_count + 1] = NULL;
    free(node->args);
    node->args = new_args;
    if (node->args[0] == NULL)
        node->args[0] = ft_strdup(arg); // Set the first argument as the command name
}

static void	handle_operator(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    t_node_type	op_type = get_ast_node_type_from_token(lexer->tokens->type);

    while (*operator_stack
        && get_operator_precedence((*operator_stack)->node->type) >= get_operator_precedence(op_type))
        process_operator(operator_stack, operand_stack);
    push_ast_stack(operator_stack, ast_new(op_type, lexer->tokens));
    advance_token(lexer);
}

static int handle_left_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack)
{
    // Push a left parenthesis node onto the operator stack
    t_ast_node *left_paren_node = ast_new(NODE_LPAREN, lexer->tokens);
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

static int handle_right_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack)
{
    // Process operators until a left parenthesis is found
    while (*operator_stack && (*operator_stack)->node->type != NODE_LPAREN)
    {
        if (!process_operator(operator_stack, operand_stack))
        {
            fprintf(stderr, "Error: Failed to process operator inside parentheses\n");
            lexer->error = 1;
            return 0;
        }
    }

    // Check if there is a matching left parenthesis
    if (!*operator_stack || (*operator_stack)->node->type != NODE_LPAREN)
    {
        fprintf(stderr, "Syntax error: unmatched right parenthesis\n");
        lexer->error = 1;
        return 0;
    }

    // Pop the left parenthesis from the stack
    pop_ast_stack(operator_stack);
    advance_token(lexer); // Move to the next token
    return 1;
}