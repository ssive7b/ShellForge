/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_redirs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:05:08 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/10 19:18:47 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast_mock.h"
#include "parser.h"
#include "utils.h"

bool	validate_redirections(t_lexer *lexer)
{
	t_token	*current;
	t_token	*next;

	current = lexer->tokens;
	while (current)
	{
		if (is_redirection_token(current->type))
		{
			next = current->next;
			while (next && next->type == TOKEN_DELIMITER)
				next = next->next;
			if (!next || !is_argument_token(next->type))
			{
				lexer->error = 1;
				ft_error_msg("minishell: syntax error: redirection without target");
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}
