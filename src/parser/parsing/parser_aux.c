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
#include "utils.h"

bool	next_token(t_lexer *lexer)
{
	if (!lexer)
	{
		ft_error_msg("Error: Lexer is NULL in next_token");
		return (false);
	}
	if (!lexer->tokens)
	{
		ft_error_msg("Warning: no more tokens to advance");
		return (false);
	}
	lexer->tokens = lexer->tokens->next;
	return (true);
}

bool	skip_delims(t_lexer *lexer)
{
	while (lexer->tokens && lexer->tokens->type == TOKEN_DELIMITER)
	{
		if (!next_token(lexer))
			return (false);
	}
	return (true);
}

bool	add_arg(t_anode *node, const char *arg)
{
	char	**new_args;
	int		arg_count;

	if (!node || !arg)
		return (false);
	arg_count = count_args(node->args);
	new_args = allocate_args_array(arg_count + 1);
	if (!new_args)
		return (false);
	if (arg_count > 0 && !copy_args(new_args, node->args, arg_count))
		return (false);
	new_args[arg_count] = safe_strdup(arg);
	if (!new_args[arg_count])
	{
		free_2d_array(&new_args, arg_count);
		return (false);
	}
	free_2d_array(&node->args, -1);
	node->args = new_args;
	return (true);
}
