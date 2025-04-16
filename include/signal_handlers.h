/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:05:30 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/16 13:41:28 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H

# include <signal.h>
# include "minishell.h"

extern volatile sig_atomic_t	g_received_signal;

typedef struct s_sighandlers
{
	struct sigaction	sa_old_int;
	struct sigaction	sa_old_quit;
}	t_sighandlers;

// signal_setup.c
void	setup_interactive_signals(void);
void	setup_parent_signals(void);
void	setup_heredoc_signals(t_sighandlers *sig_ctx);
void	restore_default_signals(void);
void	restore_heredoc_signals(t_sighandlers *sig_ctx);

// signal_handlers.c
void	sigint_prompt_handler(int signum);
void	handle_heredoc_interrupt(int signum);
void	handle_child_signal(int signum, int *exit_status);
void	exit_on_eof(t_shell *shell);

#endif
