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

char	*get_variable_name(const char *name, t_expand_context *context)
{
	char	*value;

	if (!name || !context)
		value = safe_strdup("");
	else if (ft_strcmp(name, "?") == 0)
		value = ft_itoa(context->last_exit_status);
	else
	{
		value = get_envp_value((char *)name, context->env_list);
		if (!value)
			value = safe_strdup("");
		else
			value = safe_strdup(value);
	}
	return (value);
}
