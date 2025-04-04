/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:02:25 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 14:04:54 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "types.h"
#include "minishell.h"
#include "env_utils.h"
#include "executioner.h"
#include "utils.h"

static int	setup_environment(t_shell *shell, char **envp);
static void	setup_terminal_and_io(t_shell *shell);
static int	setup_shell_context(t_shell *shell);
static int	get_terminal_fd(void);

t_shell	*init_minishell(char **envp)
{
	t_shell	*shell;

	shell = calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (!setup_environment(shell, envp))
	{
		safe_free((void **)&shell);
		return (NULL);
	}
	setup_terminal_and_io(shell);
	if (!setup_shell_context(shell))
	{
		free_env_list(shell->env_list);
		safe_free((void **)&shell);
		return (NULL);
	}
	return (shell);
}

static int	get_terminal_fd(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd < 0 && isatty(STDIN_FILENO))
		return (dup(STDIN_FILENO));
	return (fd);
}

static int	setup_environment(t_shell *shell, char **envp)
{
	int	success;

	shell->envp = envp;
	shell->env_list = create_env_list(envp);
	success = shell->env_list != NULL;
	return (success);
}

static void	setup_terminal_and_io(t_shell *shell)
{
	shell->terminal_fd = get_terminal_fd();
	shell->is_interactive = (shell->terminal_fd != -1); // checks if stdin is connected to a terminal
	if (shell->is_interactive)
		tcgetattr(STDIN_FILENO, &shell->original_term); // preserve original terminal settings so that we can restore on exit
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->std_err = dup(STDERR_FILENO);
}

static int	setup_shell_context(t_shell *shell)
{
	char	cwd_buffer[PATH_MAX];

	if (getcwd(cwd_buffer, PATH_MAX))
		shell->cwd = ft_strdup(cwd_buffer);
	else
		shell->cwd = ft_strdup(".");
	if (!shell->cwd)
		return (0);
	shell->is_running = 1;
	shell->last_exit_code = 0;
	// PLACEHOLDER FOR SIGNAL SETUP
	// E.g. setup_signals(void);
	// PLACEHOLDER FOR SIGNAL SETUP
	return (1);
}