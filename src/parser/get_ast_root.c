/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ast_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:44:10 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 16:23:32 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "expansions.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void	*get_ast_root2(t_lexer *lexer)
{
	cleanup_lexer(&lexer);
	return (NULL);
}

t_ast_node	*get_ast_root(const char *input, t_list *env_list,
		int last_exit_code)
{
	t_ast_node			*ast_root;
	t_lexer				*lexer;
	t_expand_context	context;

	if (!input || !(*input))
		return (NULL);
	lexer = run_tokenizer(input);
	if (!lexer || !lexer->tokens || lexer->error)
		get_ast_root2(lexer);
	if (!validate_input(lexer, input))
		get_ast_root2(lexer);
	context.env_list = env_list;
	context.last_exit_status = last_exit_code;
	if (!expand_variables_in_tokens(&lexer->tokens, &context))
		get_ast_root2(lexer);
	ast_root = parse_tokens(lexer);
	if (!ast_root)
		get_ast_root2(lexer);
	cleanup_lexer(&lexer);
	return (ast_root);
}
