/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:52:39 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/16 13:41:15 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <readline/readline.h>
#include "signal_handlers.h"

volatile sig_atomic_t	g_received_signal = 0;

void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_prompt_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_parent_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_heredoc_signals(t_sighandlers *sig_ctx)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_heredoc_interrupt;
	sigaction(SIGINT, &sa, &sig_ctx->sa_old_int);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, &sig_ctx->sa_old_quit);
}

void	restore_default_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	restore_heredoc_signals(t_sighandlers *sig_ctx)
{
	sigaction(SIGINT, &sig_ctx->sa_old_int, NULL);
	sigaction(SIGQUIT, &sig_ctx->sa_old_quit, NULL);
}
