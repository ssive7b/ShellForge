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

typedef struct s_tty	t_tty;

typedef struct s_expand_context
{
	t_list	*env_list;
	int     last_exit_status;
}	t_expand_context;

// expander.c
char	*get_variable_name(const char *name, t_expand_context *context);



void	expand_tokens(t_token *tokens, char **envp, int last_exit_status);
void	expand_tilde(char **token, char **envp);
void	expand_variables(char **token, char **envp, int last_exit_status);
void	replace_variable(char **line, int pos, char *var_start, char *var_value);
void	expand_wildcards(char **token);
char	*getenv_list(char **envp, const char *name);
int		valid_var_chr(char c);
char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int		match_wildcard(const char *str, const char *pattern);
char	*ft_strjoin_free(char *s1, const char *s2);

#endif
