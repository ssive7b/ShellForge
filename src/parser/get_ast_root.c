/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:44:10 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/05 00:44:11 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "expansions.h"
#include "lexer.h"
#include "utils.h"

static t_lexer	*lex_validate(const char *input, int *exit_code);
static t_anode	*build_ast(t_lexer *lexer, t_list *env_list, int *exit_code);

t_anode	*ast_root(const char *input, t_list	*env_list, int *exit_code)
{
	t_anode		*ast_root;
	t_lexer		*lexer;

	lexer = lex_validate(input, exit_code);
	if (!lexer)
		return (NULL);
	ast_root = build_ast(lexer, env_list, exit_code);
	cleanup_lexer(&lexer);
	return (ast_root);
}

static t_lexer	*lex_validate(const char *input, int *exit_code)
{
	t_lexer	*lexer;

	if (!input || !(*input))
		return (NULL);
	lexer = run_tokenizer(input);
	if (!lexer || !lexer->tokens || lexer->error)
	{
		*exit_code = 1;
		cleanup_lexer(&lexer);
		return (NULL);
	}
	if (!validate_input(lexer, input))
	{
		*exit_code = 1;
		cleanup_lexer(&lexer);
		return (NULL);
	}
	return (lexer);
}

static t_anode	*build_ast(t_lexer *lexer, t_list *env_list, int *exit_code)
{
	t_anode			*ast_root;
	t_exp_ctx		context;

	context.env_list = env_list;
	context.last_exit_status = *exit_code;
	if (!expand_variables_in_tokens(&lexer->tokens, &context))
		return (NULL);
	ast_root = parse_toks(lexer);
	return (ast_root);
}
