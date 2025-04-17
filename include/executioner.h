/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:55:10 by sstoev            #+#    #+#             */
/*   Updated: 2025/03/22 12:55:11 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include <sys/types.h>
# include <stdbool.h>
# include "types.h"
# include "../libft/include/libft.h"

// function pointer for exec mode
// t_exec_mode is a type alias for a pointer to the below func
typedef void				*(*t_exec_mode)(t_shell *sh, t_anode *node);

// Function pointer tables for passing the executioner functions pointers
typedef struct s_exec_table
{
	t_exec_mode	exec_modes[NODE_TYPES_COUNT];
}	t_exec_table;

// main executioner logic handlers
void	*exec_command(t_shell *sh, t_anode *node);
void	*exec_pipe(t_shell *sh, t_anode *node);
void	*exec_redir(t_shell *sh, t_anode *node);
void	*exec_and(t_shell *sh, t_anode *node);
void	*exec_or(t_shell *sh, t_anode *node);

// init_execs.c
void	init_exec_table(t_exec_table *exec_table);

// cmd_path_resolution.c
char	*find_cmd_path(t_shell *sh, t_list *env_list, char *cmd_name);

// exec_utils.c
pid_t	fork_extern_cmd(t_shell *sh, t_anode *node);
bool	resolve_path(t_shell *sh, t_anode *node);
void	setup_redirs(t_anode *node);
int		open_redir_flle(t_shell *sh, char *file_name, t_redir_type redir_type);

// execute.c
void	exec_ast(t_shell *sh, t_anode *node);

// pipe_setup.c
void	setup_pipe_redirs(t_anode *cmd, int pipefd[2], int is_wr);
void	close_pipe(int pipefd[2]);
bool	create_pipe(t_shell *sh, t_anode *node, int pipefd[2]);

// pipe_process.c
pid_t	fork_pipe_cmd(t_shell *sh, t_anode *cmd, int pipefd[2], int is_wr);
void	handle_fork_err(pid_t lpid, int pipefd[2]);
void	wait_pipeline(t_shell *sh, pid_t lpid, pid_t rpid, int *exit_status);
void	wait_child(t_shell *sh, pid_t cpid, int *exit_status);

// heredoc.c
int		get_hdoc_fd(t_redir *redir);

// builtins
int		is_builtin(char *cmd_name);
void	exec_builtin(t_anode *cmd);

// cd.c
void	exec_cd(t_anode *node);

// env.c
void	exec_env(t_anode *node, const t_list *env_list);

// echo.c
void	exec_echo(t_anode *node);

// exit.c
void	exec_exit(t_anode *node);

// export.c export_utils.c
void	exec_export(t_anode *node);
void	update_env_entry(t_env *existing_entry, char *value);
void	add_env_entry(char *key, char *value, t_list *env_list);
char	**get_sorted_env(t_list *env_list);
void	print_sorted_env(t_anode *node, char **sorted_env_array);

// pwd.c
void	exec_pwd(t_anode *node);

// unset.c
void	exec_unset(t_anode *node);

#endif
