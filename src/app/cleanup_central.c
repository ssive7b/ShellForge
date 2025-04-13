/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_central.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:34:32 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/12 23:44:55 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/ft_printf.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	cleanup_iteration(t_shell *shell)
{
	if (!shell)
		return ;
	safe_free((void **)&shell->input);
	if (shell->ast_root)
	{
		free_ast_node(&shell->ast_root);
		shell->ast_root = NULL;
	}
	safe_free((void **)&shell->err_msg);
	shell->error_code = 0;
	if (shell->std_in > 2)
		dup2(shell->std_in, STDIN_FILENO);
	if (shell->std_out > 2)
		dup2(shell->std_out, STDOUT_FILENO);
	if (shell->std_err > 2)
		dup2(shell->std_err, STDERR_FILENO);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->is_interactive)
		ft_printf("exit\n");
	if (shell->is_interactive && shell->terminal_fd != -1)
	{
		tcsetattr(shell->terminal_fd, TCSANOW, &shell->original_term);
		if (shell->terminal_fd != STDIN_FILENO)
			close(shell->terminal_fd);
	}
	if (shell->std_in > 2)
		close(shell->std_in);
	if (shell->std_out > 2)
		close(shell->std_out);
	if (shell->std_err > 2)
		close(shell->std_err);
	free_env_list(shell->env_list);
	cleanup_iteration(shell);
	safe_free((void **)&shell->cwd);
	safe_free((void **)&shell);
}

void	display_error(t_shell *shell)
{
	if (!shell || !shell->err_msg)
		return ;
	ft_dprintf(STDERR_FILENO, "minishell: ");
	if (shell->current_cmd)
		ft_dprintf(STDERR_FILENO, "%s: ", shell->current_cmd);
	ft_dprintf(STDERR_FILENO, "%s", shell->err_msg);
	ft_dprintf(STDERR_FILENO, "\n");
	safe_free((void **)&shell->err_msg);
}

void	set_error(t_shell *shell, int code, const char *msg)
{
	if (!shell)
		return ;
	if (shell->err_msg)
		safe_free((void **)&shell->err_msg);
	shell->error_code = code;
	if (msg)
		shell->err_msg = ft_strdup(msg);
	else
		shell->err_msg = NULL;
}
