/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:21:30 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 00:21:39 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	add_argument_to_node(t_ast_node *node, const char *arg)
{
    char	**new_args;
    int		arg_count;
    int		i;

    if (!node || !arg)
        return (false);
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
        return (false);
    }
	i = -1;
	while (++i < arg_count)
		new_args[i] = node->args[i];
    new_args[arg_count] = ft_strdup(arg);
    if (!new_args[arg_count])
    {
        perror("Error: Memory allocation failed for argument in add_argument_to_node");
        free(new_args);
        return (false);
    }
    new_args[arg_count + 1] = NULL;
    free(node->args);
    node->args = new_args;
	return (true);
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

