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

void	print_syn_err(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void	print_miss_tok(char *expected)
{
	ft_putstr_fd("minishell: syntax error: expected ", 2);
	ft_putstr_fd(expected, 2);
	ft_putstr_fd("\n", 2);
}

void	parse_err(t_lexer *lex, t_stack **ops, t_stack **opnds, t_anode **node)
{
	if (lex)
		lex->error = 1;
	if (opnds)
		stack_free(ops);
	if (opnds)
		stack_free(opnds);
	if (node && *node)
		node_free(node);
	if (!lex->error)
		ft_error_msg("minishell: syntax error in command line");
}
