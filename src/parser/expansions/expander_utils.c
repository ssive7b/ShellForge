/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:31:41 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/03 15:31:42 by sstoev           ###   ########.fr       */
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

static char	*get_var_value(const char *name, t_exp_ctx *ctx);

bool	append_chunk(char **res, const char *src, int start, int end)
{
	char	*chunk;
	bool	success;

	if (!res || !*res || !src || end <= start)
		return (true);
	chunk = ft_substr(src, start, end - start);
	if (!chunk)
		return (false);
	success = safe_strjoin(res, chunk);
	safe_free((void **)&chunk);
	return (success);
}

bool	proc_doll_sign(char **res, const char *str, int *i, t_exp_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	bool	success;

	(*i)++;
	if (str[*i] == '?')
	{
		var_value = ft_itoa(ctx->last_exit_status);
		(*i)++;
	}
	else if (is_valid_var_char(str[*i]))
	{
		var_name = extract_var_name(str, i);
		if (!var_name)
			return (false);
		var_value = get_var_value(var_name, ctx);
		safe_free((void **)&var_name);
	}
	else
		return (safe_strjoin(res, "$"));
	success = safe_strjoin(res, var_value);
	safe_free((void **)&var_value);
	return (success);
}

bool	needs_expansion(const char *str)
{
	return (str && ft_strchr(str, '$') != NULL);
}

static char	*get_var_value(const char *name, t_exp_ctx *ctx)
{
	char	*value;

	if (!name || !ctx)
		value = safe_strdup("");
	else if (ft_strcmp(name, "?") == 0)
		value = ft_itoa(ctx->last_exit_status);
	else
	{
		value = get_envp_value((char *)name, ctx->env_list);
		if (!value)
			value = safe_strdup("");
		else
			value = safe_strdup(value);
	}
	return (value);
}
