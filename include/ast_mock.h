/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_mock.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:42:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/18 12:42:53 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_MOCK_H
# define AST_MOCK_H

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type	type;
	char			*file_name;
	int				fd;
	int				open_flags;
}	t_redirection;

typedef struct	s_ast_node
{
	t_node_type	type;
	char					*cmd;
	char					**args;
	int						pid;
	int						fd_in;
	int						fd_out;
	int						exit_status;
	struct s_redirection	*redir;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}	t_ast_node;

#endif
