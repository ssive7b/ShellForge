/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/12 23:42:08 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "env_utils.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include "utils.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

static bool	process_expansion_pass(char **result, const char *str, int *pos,
				t_expand_context *context);
static char	*expand_variable_in_string(const char *str,
				t_expand_context *context);

bool	expand_variables_in_tokens(t_token **tokens, t_expand_context *context)
{
	t_token	*current;
	char	*expanded;

	if (!tokens || !*tokens || !context)
		return (true);
	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD_UNQUOTED
			|| current->type == TOKEN_WORD_DQUOTED)
		{
			if (needs_expansion(current->value))
			{
				expanded = expand_variable_in_string(current->value, context);
				if (!expanded)
					return (false);
				safe_free((void **)&current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
	return (true);
}

static char	*expand_variable_in_string(const char *str,
		t_expand_context *context)
{
	char	*result;
	int		position;

	position = 0;
	if (!str)
		return (NULL);
	if (!needs_expansion(str))
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[position])
	{
		if (!process_expansion_pass(&result, str, &position, context))
		{
			safe_free((void **)&result);
			return (NULL);
		}
		if (str[position] == '\0')
			break ;
	}
	return (result);
}

static bool	process_expansion_pass(char **result, const char *str, int *pos,
		t_expand_context *context)
{
	int	i;
	int	start;

	i = *pos;
	start = *pos;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (!append_chunk(result, str, start, i))
				return (false);
			if (!process_dollar_sign(result, str, &i, context))
				return (false);
			*pos = i;
			return (true);
		}
		i++;
	}
	if (!append_chunk(result, str, start, i))
		return (false);
	*pos = i;
	return (true);
}
