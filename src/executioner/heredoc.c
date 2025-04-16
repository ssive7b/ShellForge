/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:54:35 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/26 20:54:37 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "executioner.h"
#include "ast_mock.h"
#include "signal_handlers.h"
#include "utils.h"

static int	read_heredoc_content(int pipefd[2], t_redir *redir);

int	get_heredoc_fd(t_redir *redir)
{
	int				pipefd[2];
	int				result;
	t_sighandlers	sig_ctx;

	if (pipe(pipefd) == -1)
		return (-1);
	setup_heredoc_signals(&sig_ctx);
	result = read_heredoc_content(pipefd, redir);
	restore_heredoc_signals(&sig_ctx);
	if (result == -1)
	{
		close_pipe(pipefd);
		g_received_signal = 0;
		return (-1);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	read_heredoc_content(int pipefd[2], t_redir *redir)
{
	char	*line;
	int		result;

	result = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_received_signal == SIGINT
			|| ft_strcmp(line, redir->delimiter_heredoc) == 0)
		{
			safe_free((void **)&line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		safe_free((void **)&line);
	}
	if (g_received_signal == SIGINT)
		result = -1;
	return (result);
}