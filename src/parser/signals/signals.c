/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:52:39 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/10 21:59:38 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include "signals.h"

sig_atomic_t	g_received_signal;

// SIGINT (Ctrl-C): Show new prompt on a new line
void	sigint_prompt_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Set up the signals
// SIGINT is caught to redraw the prompt
// SIGQUIT is ignored
void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	g_received_signal = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_prompt_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// Handler for SIGINT during heredoc
// Sets global signal and closes stdin
void	handle_heredoc_interrupt(int signum)
{
	(void)signum;
	write(1, "^C\n", 3);
	g_received_signal = SIGINT;
	close(STDIN_FILENO);
}

// Resets signals in child process to default behavior
void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Handles EOF (Ctrl-D) in interactive mode
// Frees memory and exits with current status
void	exit_on_eof(t_shell *minish)
{
	int	status;

	status = minish->last_exit_code;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	exit(WEXITSTATUS(status));
}
