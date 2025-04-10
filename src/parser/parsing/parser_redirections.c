/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:18:47 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/10 21:52:26 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	redir_to_cmd2(t_lexer *l, t_redir *r, t_ast_node *c)
{
	l->error = 1;
	safe_free((void **)&r);
	clear_redirections(&(c->redirections));
}

bool	add_redirection_to_command(t_lexer *lexer, t_ast_node *cmd)
{
	t_redir	*redir;

	redir = create_redirection(lexer);
	if (!redir)
		return (false);
	advance_token(lexer);
	skip_delims(lexer);
	if (!lexer->tokens || !is_argument_token(lexer->tokens->type))
	{
		ft_error_msg("Error: Expected word after redirection");
		redir_to_cmd2(lexer, redir, cmd);
		return (false);
	}
	if (!set_redirection_target(lexer, redir))
	{
		ft_error_msg("Error: Unable to set the redirection target");
		redir_to_cmd2(lexer, redir, cmd);
		return (false);
	}
	if (!cmd->redirections)
		cmd->redirections = NULL;
	ft_lstadd_back(&cmd->redirections, ft_lstnew(redir));
	advance_token(lexer);
	return (true);
}

t_redir	*create_redirection(t_lexer *lexer)
{
	t_redir			*redir;
	t_token_type	token_type;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		ft_error_msg("Error: Failed to allocate memory for redirection");
		lexer->error = 1;
		return (NULL);
	}
	redir->fd = -1;
	redir->file_name = NULL;
	redir->delimiter_heredoc = NULL;
	redir->open_flags = 0;
	token_type = lexer->tokens->type;
	if (token_type == TOKEN_REDIR_IN)
		redir->type = REDIR_INPUT;
	else if (token_type == TOKEN_REDIR_OUT)
		redir->type = REDIR_OUTPUT;
	else if (token_type == TOKEN_REDIR_APPEND)
		redir->type = REDIR_APPEND;
	else if (token_type == TOKEN_REDIR_HEREDOC)
		redir->type = REDIR_HEREDOC;
	return (redir);
}

bool	set_redirection_target(t_lexer *lexer, t_redir *redir)
{
	char	*value;

	value = ft_strdup(lexer->tokens->value);
	if (!value)
	{
		ft_error_msg("Error: Failed to duplicate redirection target");
		lexer->error = 1;
		return (false);
	}
	if (redir->type == REDIR_HEREDOC)
		redir->delimiter_heredoc = value;
	else
		redir->file_name = value;
	return (true);
}
