/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ast_root.c                                     :+:      :+:    :+:   */
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

t_ast_node	*get_ast_root(const char *input, t_list	*env_list, int *last_exit_code)
{
	t_ast_node			*ast_root;
	t_lexer				*lexer;
	t_expand_context	context;
	
	if (!input || !(*input))
		return (NULL);
	lexer = run_tokenizer(input);
	if (!lexer || !lexer->tokens || lexer->error)
	{
		*last_exit_code = 1;
		cleanup_lexer(&lexer);
		return (NULL);
	}
	ft_print_tokens(lexer->tokens);
	if (!validate_input(lexer, input))
	{
		*last_exit_code = 1;
		cleanup_lexer(&lexer);
		return (NULL);
	}
	ft_printf("______BREAKLINE______POST_VALIDATION\n");
	context.env_list = env_list;
	context.last_exit_status = *last_exit_code;
	if (!expand_variables_in_tokens(&lexer->tokens, &context))
	{
		cleanup_lexer(&lexer);
		return (NULL);
	}
	ast_root = parse_tokens(lexer);
	if (!ast_root)
	{
		cleanup_lexer(&lexer);
		return (NULL);
	}
	cleanup_lexer(&lexer);
	return (ast_root);
}