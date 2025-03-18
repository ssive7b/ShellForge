/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:38:18 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/18 19:38:20 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	ft_execute(t_tty *minish, t_ast_node *ast_node)
{
	if (ft_is_builtin(ast_node->cmd_name))
	{
		ft_execute_builtin();
	}
	else
	{
		ft_execute_external();
	}

}
