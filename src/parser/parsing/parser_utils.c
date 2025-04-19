/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:22:42 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 00:22:43 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

bool	is_cmd_tok(t_token_type type)
{
	return (type == TOKEN_WORD_UNQUOTED
		|| type == TOKEN_WORD_DQUOTED
		|| type == TOKEN_WORD_SQUOTED);
}

bool	is_op_tok(t_token_type type)
{
	return (type == TOKEN_PIPE
		|| type == TOKEN_AND
		|| type == TOKEN_OR);
}

bool	is_arg_tok(t_token_type type)
{
	return (type == TOKEN_WORD_UNQUOTED
		|| type == TOKEN_WORD_DQUOTED
		|| type == TOKEN_WORD_SQUOTED);
}

bool	is_cmd_sep(t_token_type type)
{
	return (type == TOKEN_SEMICOLON
		|| type == TOKEN_AMPERSAND);
}

bool	is_redir_tok(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_HEREDOC);
}
