/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/03/28 23:19:08 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast_mock.h"

// parser.c
t_ast_node	*parse_tokens(t_lexer *lexer);
t_ast_node	*parse_expression(t_lexer *lexer);
bool		parse_infix_operators(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
t_ast_node	*finalize_expression(t_ast_stack **operator_stack, t_ast_stack **operand_stack, t_lexer *lexer);
t_ast_node	*parse_command_with_redirects(t_lexer *lexer);

// parser_handlers.c
bool		handle_operator_precedence(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
t_ast_node	*parse_command(t_lexer *lexer);
t_ast_node	*parse_parenthesized_expression(t_lexer *lexer);

// parser_redirections.c
bool		add_redirection_to_command(t_lexer *lexer, t_ast_node *cmd);
t_redir		*create_redirection(t_lexer *lexer);
bool 		set_redirection_target(t_lexer *lexer, t_redir *redir);

// parser_aux.c
void		advance_token(t_lexer *lexer);
bool		add_argument_to_node(t_ast_node *node, const char *arg);
void		print_stack(t_ast_stack *stack, const char *name);

// parser_utils.c
bool		is_command_token(t_token_type type);
bool		is_operator_token(t_token_type type);
bool		is_argument_token(t_token_type type);
bool 		is_command_separator(t_token_type type);
bool 		is_redirection_token(t_token_type type);

#endif