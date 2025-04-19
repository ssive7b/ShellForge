/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/03 14:54:15 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_mock.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include "env_utils.h"
#include "utils.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

static bool	proc_exp_step(char **res, char *str, int *pos, t_exp_ctx *ctx);
static char	*expand_str(char *str, t_exp_ctx *ctx);

bool	expand_variables_in_tokens(t_token **tokens, t_exp_ctx *ctx)
{
	t_token	*current;
	char	*expanded;

	if (!tokens || !*tokens || !ctx)
		return (true);
	current = *tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD_UNQUOTED
			|| current->type == TOKEN_WORD_DQUOTED)
		{
			if (needs_expansion(current->value))
			{
				expanded = expand_str(current->value, ctx);
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

static char	*expand_str(char *str, t_exp_ctx *ctx)
{
	char	*res;
	int		position;

	position = 0;
	if (!str)
		return (NULL);
	if (!needs_expansion(str))
		return (ft_strdup(str));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[position])
	{
		if (!proc_exp_step(&res, str, &position, ctx))
		{
			safe_free((void **)&res);
			return (NULL);
		}
		if (str[position] == '\0')
			break ;
	}
	return (res);
}

static bool	proc_exp_step(char **res, char *str, int *pos, t_exp_ctx *ctx)
{
	int	i;
	int	start;

	i = *pos;
	start = *pos;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (!append_chunk(res, str, start, i))
				return (false);
			if (!proc_doll_sign(res, str, &i, ctx))
				return (false);
			*pos = i;
			return (true);
		}
		i++;
	}
	if (!append_chunk(res, str, start, i))
		return (false);
	*pos = i;
	return (true);
}
