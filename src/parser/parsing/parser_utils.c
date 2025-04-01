#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

void	advance_token(t_lexer *lexer)
{
	if (!lexer)
	{
		perror("Error: Lexer is NULL in advance_token\n");
		return ;
	}
	if (!lexer->tokens)
	{
		perror("Warning: no more tokens to advance\n");
		return ;
	}
	if (lexer->tokens)
		lexer->tokens = lexer->tokens->next;
}

int	is_command_token(t_token_type type)
{
    return (type == TOKEN_WORD_UNQUOTED
        || type == TOKEN_WORD_DQUOTED
        || type == TOKEN_WORD_SQUOTED);
}

int	is_operator_token(t_token_type type)
{
    return (type == TOKEN_PIPE
        || type == TOKEN_AND
        || type == TOKEN_OR
        || type == TOKEN_REDIR_OUT
        || type == TOKEN_REDIR_IN
        || type == TOKEN_REDIR_APPEND
        || type == TOKEN_REDIR_HEREDOC);
}

int	is_argument_token(t_token_type type)
{
    return (type == TOKEN_WORD_UNQUOTED
        || type == TOKEN_WORD_DQUOTED
        || type == TOKEN_WORD_SQUOTED);
}

void	add_argument_to_node(t_ast_node *node, const char *arg)
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
}

void	print_stack(t_ast_stack *stack, const char *name)
{
    printf("Stack %s:\n", name);
    while (stack)
    {
        printf("  Node type: %d\n", stack->node->type);
		printf("  Node pathname: %s\n", stack->node->cmd_pathname);
        stack = stack->next;
    }
}