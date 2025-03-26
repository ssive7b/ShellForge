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
# include "../libft/include/libft.h"
# include "ast_mock.h"

typedef struct s_tty		t_tty;
typedef enum e_node_type	t_node_type;
typedef struct s_env		t_env;
typedef struct s_ast_node	t_ast_node;

// function pointer for exec mode
// t_exec_mode is a type alias for a pointer to the below func
typedef void				*(*t_exec_mode)(t_tty *sh, t_ast_node *node);

// Function pointer tables for passing the executioner functions pointers
typedef struct s_exec_table
{
	t_exec_mode	exec_modes[NODE_TYPES_COUNT];
}	t_exec_table;

// main executioner logic handlers
void	*execute_command(t_tty *sh, t_ast_node *node);
void	*execute_pipe(t_tty *sh, t_ast_node *node);
void	*execute_redirection(t_tty *sh, t_ast_node *node);
void	*execute_and(t_tty *sh, t_ast_node *node);
void	*execute_or(t_tty *sh, t_ast_node *node);

// init_execs.c
void	init_exec_table(t_exec_table *exec_table);

// exec_utils.c
void	setup_redirections(t_ast_node *node);
pid_t	fork_and_execute_child(t_tty *sh, t_ast_node *node);
void	wait_for_child(pid_t cpid, int *exit_status);
int		open_redirection_flle(const char *file_name, t_redir_type redir_type);

// execute.c
void	exec_astree(t_tty *sh, t_ast_node *node);

// builtins
int		is_builtin(char *cmd_name);
void	exec_builtin(t_ast_node *cmd_node);

// cd.c
void	exec_cd(t_ast_node *node);

// env.c
void	exec_env(t_ast_node *node, const t_list *env_list);

// echo.c
void	exec_echo(t_ast_node *node);

// exit.c
void	exec_exit(t_ast_node *node);

// export.c export_utils.c
void	exec_export(t_ast_node *node);
void 	update_existing_env_entry(t_env *existing_entry, char *value);
void	add_new_env_entry(char *key, char *value, t_list *env_list);
char 	**get_sorted_env_array(t_list *env_list);
void 	print_sorted_env_list(t_ast_node *node, char **sorted_env_array);

// pwd.c
char	**get_cwd(void);
void	exec_pwd(t_ast_node *node);

// unset.c
void	exec_unset(t_ast_node *node);

#endif
