/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:51:48 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 15:51:50 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_shell			t_shell;
typedef struct s_token			t_token;
typedef struct s_expand_context	t_exp_ctx;
typedef struct s_redirection	t_redir;
typedef struct s_ast_node		t_anode;
typedef struct s_ast_stack		t_stack;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_history		t_history;

# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''
# define PIPE '|'

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_AND,
	NODE_OR,
	NODE_LPAREN,
	NODE_RPAREN,
	NODE_TYPES_COUNT
}	t_ntype;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef enum e_token_type
{
	TOKEN_UNKNOWN,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_AMPERSAND,
	TOKEN_SEMICOLON,
	TOKEN_WORD_UNQUOTED,
	TOKEN_WORD_DQUOTED,
	TOKEN_WORD_SQUOTED,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_DELIMITER,
	TOKEN_END
}	t_token_type;

#endif
