/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 20:29:50 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast_mock.h"
# include "lexer.h"
# include "types.h"

// parser.c
t_ast_node	*parse_tokens(t_lexer *lexer);
t_ast_node	*parse_expression(t_lexer *lexer, t_ast_stack **operator_stack,
				t_ast_stack **operand_stack);
bool		parse_infix_operators(t_lexer *lexer, t_ast_stack **operator_stack,
				t_ast_stack **operand_stack);
t_ast_node	*finalize_expression(t_ast_stack **operator_stack,
				t_ast_stack **operand_stack, t_lexer *lexer);
t_ast_node	*parse_command_with_redirects(t_lexer *lexer,
				t_ast_stack **operator_stack, t_ast_stack **operand_stack);

// parser_ast_init.c
t_ast_node	*ast_new(t_node_type type, t_token *token);

// parser_ast_utils.c
int			op_precedence(t_node_type type);
int			push_ast_stack(t_ast_stack **stack, t_ast_node *node);
t_ast_node	*pop_ast_stack(t_ast_stack **stack);
bool		process_operator(t_ast_stack **operator_stack,
				t_ast_stack **operand_stack);
t_node_type	get_ast_node_type_from_token(t_token_type type);

// parser_handlers.c
bool		handle_operator_precedence(t_lexer *lexer,
				t_ast_stack **operator_stack, t_ast_stack **operand_stack);
void		*parse_cmd2(t_lexer *lexer);
t_ast_node	*parse_command(t_lexer *lexer);
t_ast_node	*parse_parenthesized_expression(t_lexer *lexer,
				t_ast_stack **operator_stack, t_ast_stack **operand_stack);

// parser_redirections.c
void		redir_to_cmd2(t_lexer *l, t_redir *r, t_ast_node *c);
bool		add_redirection_to_command(t_lexer *lexer, t_ast_node *cmd);
t_redir		*create_redirection(t_lexer *lexer);
bool		set_redirection_target(t_lexer *lexer, t_redir *redir);

// parser_aux.c
bool		advance_token(t_lexer *lexer);
bool		skip_delims(t_lexer *lexer);
bool		add_argument_to_node(t_ast_node *node, const char *arg);

// parser_utils.c
bool		is_command_token(t_token_type type);
bool		is_operator_token(t_token_type type);
bool		is_argument_token(t_token_type type);
bool		is_command_separator(t_token_type type);
bool		is_redirection_token(t_token_type type);

// validation
// parser_validation.c
bool		validate_input(t_lexer *lexer, const char *input);
bool		validate_quotes(const char *input);
bool		validate_parentheses(t_lexer *lexer);

// parser_validation_redirs.c
bool		validate_redirections(t_lexer *lexer);

// parser_validation_operators.c
bool		v_ops3(t_lexer *l);
bool		v_ops2(t_lexer *l, t_token *c);
bool		validate_operators(t_lexer *lexer);
bool		validate_pipes(t_lexer *lexer);

// parser_mem_cleaners.c
void		free_ast_node(t_ast_node **node);
void		free_ast_stack(t_ast_stack **stack);
void		cleanup_parser_state(t_ast_stack **operator_stack,
				t_ast_stack **operand_stack, t_ast_node **node);
void		clear_redirections(t_list **redirections);
void		free_redirection(t_redir **redir);

// parser_error_handling.c
void		handle_parser_error(t_lexer *lexer, t_ast_stack **operator_stack,
				t_ast_stack **operand_stack, t_ast_node **node);
void		print_syntax_error(char *token);
void		print_missing_token_error(char *expected);

// get_ast_root.c
void		*get_ast_root2(t_lexer *lexer);
t_ast_node	*get_ast_root(const char *input, t_list *env_list,
				int last_exit_code);

#endif