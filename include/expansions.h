/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 23:15:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/03 14:13:26 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "../libft/include/libft.h"

typedef struct s_expand_context
{
	t_list	*env_list;
	int		last_exit_status;
}	t_exp_ctx;

// expander.c
bool	expand_variables_in_tokens(t_token **tokens, t_exp_ctx *ctx);

// expander_utils.c
bool	append_chunk(char **result, const char *src, int start, int end);
bool	proc_doll_sign(char **result, const char *str, int *i, t_exp_ctx *ctx);
bool	needs_expansion(const char *str);

#endif
