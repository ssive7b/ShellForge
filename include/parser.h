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

# include "types.h"
# include "ast_mock.h"
# include "lexer.h"

// parser.c
t_anode	*parse_toks(t_lexer *lex);
t_anode	*parse_expr(t_lexer *lex, t_stack **ops, t_stack **opnds);
bool	parse_infix(t_lexer *lex, t_stack **ops, t_stack **opnds);
t_anode	*finalize_expr(t_stack **ops, t_stack **opnds, t_lexer *lex);
t_anode	*parse_cmd_redir(t_lexer *lex, t_stack **ops, t_stack **opnds);

// parser_ast_init.c
t_anode	*node_new(t_ntype type, t_token *tok);

// parser_ast_utils.c
int		op_precedence(t_ntype type);
int		stack_push(t_stack **stack, t_anode *node);
t_anode	*stack_pop(t_stack **stack);
bool	apply_op(t_stack **ops, t_stack **opnds);
t_ntype	tok_to_node(t_token_type type);

// parser_handlers.c
bool	handle_op_prec(t_lexer *lex, t_stack **ops, t_stack **opnds);
t_anode	*parse_cmd(t_lexer *lex);
t_anode	*parse_paren_expr(t_lexer *lex, t_stack **ops, t_stack **opnds);
bool	parse_command_arguments(t_lexer *lex, t_anode *cmd);

// parser_redirections.c
bool	add_redir(t_lexer *lex, t_anode *cmd);
t_redir	*new_redir(t_lexer *lex);
bool	set_redir_tgt(t_lexer *lex, t_redir *redir);

// parser_aux.c
bool	next_token(t_lexer *lex);
bool	skip_delims(t_lexer *lex);
bool	add_arg(t_anode *node, const char *arg);

// parser_utils.c
bool	is_cmd_tok(t_token_type type);
bool	is_op_tok(t_token_type type);
bool	is_arg_tok(t_token_type type);
bool	is_cmd_sep(t_token_type type);
bool	is_redir_tok(t_token_type type);

// validation
// parser_validation.c
bool	validate_input(t_lexer *lex, const char *input);
bool	validate_quotes(const char *input);
bool	validate_parens(t_lexer *lex);

// parser_validation_redirs.c
bool	validate_redirs(t_lexer *lex);

// parser_validation_operators.c
bool	validate_ops(t_lexer *lex);
bool	validate_pipes(t_lexer *lex);

// parser_mem_cleaners.c
void	node_free(t_anode **node);
void	stack_free(t_stack **stack);
void	parser_cleanup(t_stack **ops, t_stack **opnds, t_anode **node);
void	clr_redirs(t_list **redirs);
void	del_redir(void *content);

// parser_error_handling.c
void	parse_err(t_lexer *lex, t_stack **ops, t_stack **opnds, t_anode **node);
void	print_syn_err(char *tok);
void	print_miss_tok(char *expected);

// ast_root.c
t_anode	*ast_root(const char *input, t_list	*env_list, int *exit_code);

#endif