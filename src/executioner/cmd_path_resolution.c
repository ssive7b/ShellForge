/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:51 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/05 13:30:52 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "executioner.h"
#include "lexer.h"
#include "minishell.h"
#include "ast_mock.h"
#include "env_utils.h"
#include "utils.h"

static bool	is_command_executable(const char *path, t_shell *sh);
static char	*try_direct_execution(const char *cmd, t_shell *sh);
static char	*try_current_directory(const char *cmd, t_shell *sh);
static char	*search_in_path(const char *cmd, const char *path_value, t_shell *sh);

char	*find_exec_pathname(t_shell *sh, t_list *env_list, char *cmd_name)
{
	char	*direct_path;
	char	*path_value;

	if (!cmd_name || !*cmd_name)
		return (NULL);
	direct_path = try_direct_execution(cmd_name, sh);
	if (direct_path)
		return (direct_path);
	path_value = get_envp_value("PATH", env_list);
	if (!path_value || !(*path_value))
		return (try_current_directory(cmd_name, sh));
	return (search_in_path(cmd_name, path_value, sh));
}

static bool	is_command_executable(const char *path, t_shell *sh)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		set_error(sh, 127, "No such file or directory");
		return (false);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		set_error(sh, 126, "Is a directory");
		return (false);
	}
	if (!(statbuf.st_mode & S_IXUSR))
	{
		set_error(sh, 126, "Permission denied");
		return (false);
	}
	return (true);
}

static char	*try_direct_execution(const char *cmd, t_shell *sh)
{
	if (!ft_strchr(cmd, '/'))
		return (NULL);
	if (is_command_executable(cmd, sh))
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*try_current_directory(const char *cmd, t_shell *sh)
{
	char	*path;
	bool	executable;

	path = ft_strjoin_multiple((char *[]){"./", (char *)cmd}, 2);
	if (!path)
		return (NULL);
	executable = (access(path, F_OK | X_OK) == 0);
	if (!executable)
	{
		free(path);
		set_error(sh, 127, "Command not found");
		return (NULL);
	}
	return (path);
}

static char	*search_in_path(const char *cmd, const char *path_value, t_shell *sh)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin_multiple((char *[]){paths[i], "/", (char *)cmd}, 3);
		if (!full_path)
		{
			ft_free_2d_array(&paths, -1);
			return (NULL);
		}
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_2d_array(&paths, -1);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_2d_array(&paths, -1);
	set_error(sh, 127, "Command not found");
	return (NULL);
}
