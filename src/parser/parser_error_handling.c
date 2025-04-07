/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:55:41 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/07 21:55:42 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void	print_missing_token_error(char *expected)
{
	ft_putstr_fd("minishell: syntax error: expected ", 2);
	ft_putstr_fd(expected, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_parser_error(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_ast_node **node)
{
	if (lexer)
		lexer->error = 1;
	if (operand_stack)
		free_ast_stack(operator_stack);
	if (operand_stack)
		free_ast_stack(operand_stack);
	if (node && *node)
		free_ast_node(node);
	if (!lexer->error)
		ft_error_msg("minishell: syntax error in command line");
}
