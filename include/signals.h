/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:05:30 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/13 16:41:52 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	sigint_prompt_handler(int signum);
void	setup_interactive_signals(void);
void	handle_heredoc_interrupt(int signum);
void	restore_default_signals(void);
void	exit_on_eof(t_shell *minish);

#endif