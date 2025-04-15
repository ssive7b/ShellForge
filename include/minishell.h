#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include "types.h"
# include "../libft/include/libft.h"
# include "termios.h"

# define SHELL_PROMPT "minishell$> "

typedef struct	s_shell
{
	char			*input;
	t_ast_node		*ast_root;
	char			**envp;				// raw env array for execve
	t_list			*env_list;			// linked list for easy manipulation
	char			*cwd;
	char			*current_cmd;
	int				last_exit_code;
	int				is_running;			// control variable for the main loop
	int				is_interactive;
	struct termios	original_term;		// saved original settings
	int				terminal_fd;		// fd of the original terminal (tty)
	int				std_in;				// original stdin
	int				std_out;			// original stdout
	int				std_err;			// original stderr
	char			*err_msg;			// error message- human readable
}	t_shell;

// inits.c
t_shell	*init_minishell(char **envp);

// cleanup_central.c
void	cleanup_iteration(t_shell *shell);
void	cleanup_shell(t_shell *shell);
void	display_error(t_shell *shell);
void	set_error(t_shell *shell, int code, const char *msg);
void	update_exit_code(t_shell *sh, t_ast_node *node);

#endif