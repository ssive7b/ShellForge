/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:55:10 by sstoev            #+#    #+#             */
/*   Updated: 2025/04/13 16:42:06 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include "../libft/include/libft.h"
# include "types.h"
# include <stdbool.h>
# include <sys/types.h>

// function pointer for exec mode
// t_exec_mode is a type alias for a pointer to the below func
typedef void	*(*t_exec_mode)(t_shell *sh, t_ast_node *node);

// Function pointer tables for passing the executioner functions pointers
typedef struct s_exec_table
{
	t_exec_mode	exec_modes[NODE_TYPES_COUNT];
}				t_exec_table;

// main executioner logic handlers
void			*execute_command(t_shell *sh, t_ast_node *node);
void			*execute_pipe(t_shell *sh, t_ast_node *node);
void			*execute_redirection(t_shell *sh, t_ast_node *node);
void			*execute_and(t_shell *sh, t_ast_node *node);
void			*execute_or(t_shell *sh, t_ast_node *node);

// init_execs.c
void			init_exec_table(t_exec_table *exec_table);

// cmd_path_resolution.c
char			*find_exec_pathname(t_shell *sh, t_list *env_list,
					char *cmd_name);

// exec_utils.c
pid_t			fork_external_command(t_shell *sh, t_ast_node *node);
bool			resolve_command_path(t_shell *sh, t_ast_node *node);
void			setup_redirections(t_ast_node *node);
int				open_redirection_flle(t_shell *sh, const char *file_name,
					t_redir_type redir_type);

// execute.c
void			exec_astree(t_shell *sh, t_ast_node *node);

// pipe_utils.c
bool			prepare_pipe_commands(t_shell *sh, t_ast_node *node);
pid_t			fork_pipe_process(t_shell *sh, t_ast_node *cmd_node,
					int pipefd[2], int is_writer);
void			execute_pipe_child(t_shell *sh, t_ast_node *cmd_node,
					int pipefd[2], int is_writer);
void			handle_fork_error(pid_t left_pid, int pipefd[2]);
void			wait_for_pipeline(t_shell *sh, pid_t left_pid, pid_t right_pid,
					int *exit_status);
void			close_pipe(int pipefd[2]);
void			wait_for_child(t_shell *sh, pid_t cpid, int *exit_status);
bool			create_pipe(t_shell *sh, t_ast_node *node, int pipefd[2]);

// heredoc.c
int				get_heredoc_fd(t_redir *redir);

// builtins
int				is_builtin(char *cmd_name);
void			exec_builtin(t_ast_node *cmd_node);

// cd.c
void			exec_cd(t_ast_node *node);

// env.c
void			exec_env(t_ast_node *node, const t_list *env_list);

// echo.c
void			exec_echo(t_ast_node *node);

// exit.c
void			exec_exit(t_ast_node *node);

// export.c export_utils.c
void			export_var2(char *var, t_list *env_list);
void			exec_export(t_ast_node *node);
void			update_existing_env_entry(t_env *existing_entry, char *value);
void			add_new_env_entry(char *key, char *value, t_list *env_list);
char			**get_sorted_env_array(t_list *env_list);
void			print_sorted_env_list(t_ast_node *node,
					char **sorted_env_array);

// pwd.c
char			**get_cwd(void);
void			exec_pwd(t_ast_node *node);

// unset.c
void			exec_unset(t_ast_node *node);

#endif
