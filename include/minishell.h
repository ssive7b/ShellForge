/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:51:36 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/16 15:51:37 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include <termios.h>
# include "types.h"
# include "../libft/include/libft.h"

# define SHELL_PROMPT "minishell$> "

typedef struct s_shell
{
	char			*input;
	t_anode			*ast_root;
	char			**envp;
	t_list			*env_list;
	char			*cwd;
	char			*current_cmd;
	int				last_exit_code;
	int				is_running;
	int				is_interactive;
	struct termios	original_term;
	int				terminal_fd;
	int				std_in;
	int				std_out;
	int				std_err;
	char			*err_msg;
}	t_shell;

// inits.c
t_shell	*init_minishell(char **envp);

// cleanup_central.c
void	cleanup_iteration(t_shell *shell);
void	cleanup_shell(t_shell *shell);
void	display_error(t_shell *shell);
void	set_error(t_shell *shell, int code, const char *msg);
void	update_exit_code(t_shell *sh, t_anode *node);

#endif
