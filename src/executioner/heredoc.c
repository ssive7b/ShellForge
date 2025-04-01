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

int	get_heredoc_fd(t_redir *redir)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->delimiter_heredoc) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
