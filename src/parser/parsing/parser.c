#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

// Work on error messages!!

static t_ast_node	*parse_pipeline(t_lexer *lexer);
static t_ast_node	*parse_command(t_lexer *lexer);
static t_ast_node	*parse_redirect(t_lexer *lexer);
static t_ast_node	*create_ast_node(t_node_type type, t_token *token);
static void			advance_token(t_lexer *lexer);
static void			handle_empty_command(t_lexer *lexer);
static void			handle_invalid_redirection(t_lexer *lexer);

// Main parser function
t_ast_node	*parse_input(t_lexer *lexer)
{
	t_ast_node	*ast_root;
	t_ast_stack	*op_stack;
	t_ast_stack	*operand_stack;

	ast_root = NULL;
	op_stack = NULL;
	operand_stack = NULL;
	while (lexer->tokens)
	{
		// Error handling for empty command
		handle_empty_command(lexer);
		// Parsing pipeline or redirection
		if (lexer->tokens->type == TOKEN_PIPE)
			ast_root = parse_pipeline(lexer);
		else if (lexer->tokens->type == TOKEN_REDIR_OUT
			|| lexer->tokens->type == TOKEN_REDIR_IN
			|| lexer->tokens->type == TOKEN_REDIR_APPEND
			|| lexer->tokens->type == TOKEN_REDIR_HEREDOC)
		{
			// Handle invalid redirection operator errors
			handle_invalid_redirection(lexer);
			ast_root = parse_redirect(lexer);
		}
		else
			ast_root = parse_command(lexer);
		// Push the node to the operand stack
		push_ast_stack(&operand_stack, ast_root);
		// Handle operators (AND, OR) precedence here if necessary
		if (lexer->tokens && (lexer->tokens->type == TOKEN_AND
				|| lexer->tokens->type == TOKEN_OR))
			process_the_operators(&op_stack, &operand_stack);
		if (lexer->error)
			return (NULL);
	}
	// Return the root of the constructed AST
	return (pop_ast_stack(&operand_stack));
}

// Handle empty command error
static void	handle_empty_command(t_lexer *lexer)
{
	if (lexer->tokens && lexer->tokens->type == ' ')
	{
		fprintf(stderr, "Syntax error: empty command.\n");
		lexer->error = 1; // Flag error
	}
}

// Parsing a pipeline (e.g., `command1 | command2`)
static t_ast_node	*parse_pipeline(t_lexer *lexer)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;

	left = parse_command(lexer);
	if (!left)
		return (NULL);
	// Advance past the PIPE token
	advance_token(lexer);
	right = parse_command(lexer);
	if (!right)
		return (NULL);
	// Create a node for the pipeline
	node = create_ast_node(NODE_PIPE, lexer->tokens);
	node->left = left;
	node->right = right;
	return (node);
}

// Parsing a command (e.g., `command arg1 arg2`)
static t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*node;

	// Check for the next token being a command word
	if (lexer->tokens && (lexer->tokens->type == TOKEN_WORD_UNQUOTED
			|| lexer->tokens->type == TOKEN_WORD_SQUOTED
			|| lexer->tokens->type == TOKEN_WORD_DQUOTED))
	{
		node = create_ast_node(NODE_COMMAND, lexer->tokens);
		// Parse arguments
		lexer->tokens = lexer->tokens->next;
		// Check if there are more arguments
		while (lexer->tokens && (lexer->tokens->type == TOKEN_WORD_UNQUOTED
				|| lexer->tokens->type == TOKEN_WORD_SQUOTED
				|| lexer->tokens->type == TOKEN_WORD_DQUOTED))
		{
			// Add arguments to the node
			// You would need to append to the args array here
			lexer->tokens = lexer->tokens->next;
		}
		return (node);
	}
	return (NULL);
}

// Parsing redirections (e.g., `command > file`)
static t_ast_node	*parse_redirect(t_lexer *lexer)
{
	t_ast_node		*node;
	t_redirection	*redir_data;

	redir_data = malloc(sizeof(t_redirection));
	if (!redir_data)
	{
		lexer->error = 1;
		return (NULL);
	}
	// Create redirection node
	node = create_ast_node(NODE_REDIRECTION, lexer->tokens);
	if (lexer->tokens->type == TOKEN_REDIR_OUT)
		redir_data->type = REDIR_OUTPUT;
	else if (lexer->tokens->type == TOKEN_REDIR_IN)
		redir_data->type = REDIR_INPUT;
	else if (lexer->tokens->type == TOKEN_REDIR_APPEND)
		redir_data->type = REDIR_APPEND;
	else if (lexer->tokens->type == TOKEN_REDIR_HEREDOC)
		redir_data->type = REDIR_HEREDOC;
	node->redir = redir_data;
	// Advance past the redirection operator
	advance_token(lexer);
	// Get the file for the redirection
	if (lexer->tokens && (lexer->tokens->type == TOKEN_WORD_UNQUOTED
			|| lexer->tokens->type == TOKEN_WORD_SQUOTED
			|| lexer->tokens->type == TOKEN_WORD_DQUOTED))
	{
		redir_data->file_name = lexer->tokens->value;
		// Advance past the file name
		advance_token(lexer);
	}
	else
	{
		fprintf(stderr, "Syntax error: missing file for redirection.\n");
		lexer->error = 1; // Flag error
		return (NULL);
	}
	// Handle special case for HEREDOC (delimiter)
	if (redir_data->type == REDIR_HEREDOC && lexer->tokens
		&& lexer->tokens->type == TOKEN_WORD_UNQUOTED)
	{
		redir_data->delimiter_heredoc = lexer->tokens->value;
		advance_token(lexer);
	}
	return (node);
}

static void	handle_invalid_redirection(t_lexer *lexer)
{
	if (lexer->tokens && (lexer->tokens->type == TOKEN_REDIR_OUT
			|| lexer->tokens->type == TOKEN_REDIR_IN
			|| lexer->tokens->type == TOKEN_REDIR_APPEND
			|| lexer->tokens->type == TOKEN_REDIR_HEREDOC))
	{
		fprintf(stderr, "Syntax error: invalid redirection operator.\n");
		lexer->error = 1; // Flag error
	}
}

// Create a new AST node based on a token
static t_ast_node	*create_ast_node(t_node_type type, t_token *token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd_pathname = token->value;
	node->args = NULL; // You'll need to handle argument parsing
	node->pid = 0;
	node->fd_in = -1;
	node->fd_out = -1;
	node->exit_status = 0;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Advance the lexer token
static void	advance_token(t_lexer *lexer)
{
	if (lexer->tokens)
		lexer->tokens = lexer->tokens->next;
}

// Process operators for precedence (AND, OR, PIPE)
// Handle precedence and push/pop from the operator and operand stacks
// Logic depends on the precedence of the operators, which needs to be determined
	// using the `get_operator_precedence` function.
void process_the_operators(t_ast_stack **op_stack, t_ast_stack **operand_stack)
{
	t_ast_node	*node;
	t_ast_node	*right;
	t_ast_node	*left;

	while (*op_stack
		&& get_operator_precedence((*op_stack)->node->type) >= get_operator_precedence((*operand_stack)->node->type))
	{
		right = pop_ast_stack(operand_stack);
		left = pop_ast_stack(operand_stack);
		node = pop_ast_stack(op_stack);
		node->left = left;
		node->right = right;
		push_ast_stack(operand_stack, node);
	}
}

char	*handle_quotes(t_lexer *lx, char quote_type)
{
	size_t	start_idx;
	char	*quoted_str;

	lx->idx++; // Skip opening quote
	start_idx = lx->idx;
	while (lx->input[lx->idx] && lx->input[lx->idx] != quote_type)
		lx->idx++;
	// Error: Unclosed quote
	if (lx->input[lx->idx] != quote_type)
	{
		printf("Syntax error: unclosed %c quote\n", quote_type);
		return (NULL);
	}
	// Extract quoted content (without quotes)
	quoted_str = ft_substr(lx->input, start_idx, lx->idx - start_idx);
	lx->idx++; // Skip closing quote
	return (quoted_str);
}
