#ifndef MINISHELL_H
# define MINISHELL_H

# include <linux/limits.h>
# include "../libft/include/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_tty
{
	char				*cwd;
	char				*prompt;
	char				*line;
	struct s_list		*env_list;
	struct s_ast_node	*ast_tree;
	int					exit_status;
	char				**envp;
}	t_tty;

// inits.c
void	*init_minishell(t_tty *minish, char **envp);

#endif