/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_mock.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:42:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/27 07:29:31 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_MOCK_H
# define AST_MOCK_H

# include "lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_AND,
	NODE_OR,
	NODE_TYPES_COUNT
}							t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*file_name;
	char					*delimiter_heredoc;
	int						fd;
	int						open_flags;
}							t_redirection;

typedef struct s_ast_node
{
	t_node_type				type;
	char					*cmd_pathname;
	char					**args;
	int						pid;
	int						fd_in;
	int						fd_out;
	int						exit_status;
	struct s_redirection	*redir;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}							t_ast_node;

typedef struct s_ast_stack
{
	t_ast_node				*node;
	struct s_ast_stack		*next;
}							t_ast_stack;

t_ast_node					*ast_new(t_node_type type, t_token *token);
int							get_operator_precedence(t_node_type type);
void						push_ast_stack(t_ast_stack **stack,
								t_ast_node *node);
t_ast_node					*pop_ast_stack(t_ast_stack **stack);
void						process_operator(t_ast_stack **op_stack,
								t_ast_stack **operand_stack);
t_ast_node					*construct_ast(t_token *tokens);
t_node_type					get_ast_node_type_from_token(t_token_type type);
void						print_ast(t_ast_node *node, int level);

#endif
