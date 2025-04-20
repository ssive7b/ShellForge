/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:18:47 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/02 00:18:49 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

static bool	fail_redir(t_lexer *lex, t_anode *cmd, t_redir **redir, char *msg);

bool	add_redir(t_lexer *lexer, t_anode *cmd)
{
	t_redir	*redir;

	redir = new_redir(lexer);
	if (!redir)
		return (false);
	next_token(lexer);
	skip_delims(lexer);
	if (!lexer->tokens || !is_arg_tok(lexer->tokens->type))
		return (fail_redir(lexer, cmd, &redir,
				"Error: Expected word after redirection"));
	if (!set_redir_tgt(lexer, redir))
		return (fail_redir(lexer, cmd, &redir,
				"Error: Unable to set the redirection target"));
	if (!cmd->redirs)
		cmd->redirs = NULL;
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	return (true);
}

t_redir	*new_redir(t_lexer *lexer)
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

bool	set_redir_tgt(t_lexer *lexer, t_redir *redir)
{
	char	*value;

	value = join_consecutive_tokens(lexer);
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

static bool	fail_redir(t_lexer *lex, t_anode *cmd, t_redir **redir, char *msg)
{
	ft_error_msg(msg);
	lex->error = 1;
	safe_free((void **)redir);
	clr_redirs(&(cmd->redirs));
	return (false);
}
