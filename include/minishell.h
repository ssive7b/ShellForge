/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:40:46 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 16:44:14 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "termios.h"
# include "types.h"
# include <linux/limits.h>

# define SHELL_PROMPT "minishell$> "

typedef struct s_shell
{
	char			*input;
	t_ast_node		*ast_root;
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
	int				error_code;
}					t_shell;

// inits.c
t_shell				*init_minishell(char **envp);

// cleanup_central.c
void				cleanup_iteration(t_shell *shell);
void				cleanup_shell(t_shell *shell);
void				display_error(t_shell *shell);
void				set_error(t_shell *shell, int code, const char *msg);

#endif