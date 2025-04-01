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

// parser_handlers.c
t_ast_node	*parse_command(t_lexer *lexer);
void		handle_operator(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);
int 		handle_left_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack);
int 		handle_right_parenthesis(t_lexer *lexer, t_ast_stack **operator_stack, t_ast_stack **operand_stack);

// parser_utils.c
void		advance_token(t_lexer *lexer);
int			is_command_token(t_token_type type);
int			is_operator_token(t_token_type type);
int			is_argument_token(t_token_type type);
void		add_argument_to_node(t_ast_node *node, const char *arg);
void		print_stack(t_ast_stack *stack, const char *name);

#endif