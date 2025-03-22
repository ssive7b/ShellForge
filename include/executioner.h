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

// pwd
char	**get_cwd(void);
void	exec_pwd(t_list *env_list);

#endif
