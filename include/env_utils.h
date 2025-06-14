/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:50:10 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 15:50:11 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

// env_init.c
t_list	*create_env_list(char **envp);
void	free_env_content(void *content);
void	free_env_list(t_list *env_list);
t_list	**get_env(void);

// env_aux.c
t_list	*to_env_node(char *env_str);
char	*get_envp_value(char *key, t_list *env_list);
t_env	*get_env_entry(char *key, t_list *env_list);
t_list	*create_env_node(char *key, char *value);

// env_utils.c
bool	is_valid_var_char(char c);
char	*extract_var_name(const char *str, int *i);

// env_default.c
t_list	*create_minimal_env(void);

#endif
