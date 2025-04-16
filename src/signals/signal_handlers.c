/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:52:39 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/16 13:41:04 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <readline/readline.h>
#include "signal_handlers.h"

void	sigint_prompt_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_heredoc_interrupt(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "^C\n", 3);
	g_received_signal = SIGINT;
	close(STDIN_FILENO);
}

void	handle_child_signal(int signum, int *exit_status)
{
	*exit_status = 128 + signum;
	if (signum == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
	else if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

void	exit_on_eof(t_shell *shell)
{
	int	status;

	status = shell->last_exit_code;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	cleanup_shell(shell);
	exit(WEXITSTATUS(status));
}
