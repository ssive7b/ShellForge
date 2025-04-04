/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:02:25 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 14:04:54 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "types.h"
# include "minishell.h"
# include "env_utils.h"
# include "executioner.h"

void	*init_minishell(t_shell *minish, char **envp)
{
	minish->env_list = *get_env();
	minish->cwd = *get_cwd();
	minish->prompt = "minishell$> ";
	minish->line = NULL;
	minish->envp = envp;
	minish->exit_status = 0;
	minish->ast_tree = NULL;
	return (NULL);
}